/**
 * @file app.js
 * @brief Functional Admin Panel logic with localStorage-based CRUD.
 *
 * This JavaScript module handles all frontend operations for the
 * Student Database Management System admin panel, including:
 *   - Add / Edit / Delete student records
 *   - Search and filter functionality
 *   - Dashboard statistics
 *   - Toast notifications
 *   - Section-based navigation
 *
 * Course: CSE 124 - Data Structure Lab
 * Institution: Daffodil International University
 */

/* ══════════════════════════════════════════════════════════════
   DATA LAYER — localStorage
   ══════════════════════════════════════════════════════════════ */

const STORAGE_KEY = 'student_dbms_records';

/** Retrieve all student records from localStorage. */
function getStudents() {
    try {
        const data = localStorage.getItem(STORAGE_KEY);
        return data ? JSON.parse(data) : [];
    } catch (e) {
        console.error('Error reading from storage:', e);
        return [];
    }
}

/** Save the student array to localStorage. */
function saveStudents(students) {
    try {
        localStorage.setItem(STORAGE_KEY, JSON.stringify(students));
    } catch (e) {
        console.error('Error writing to storage:', e);
        showToast('Failed to save data.', 'error');
    }
}

/* ══════════════════════════════════════════════════════════════
   NAVIGATION
   ══════════════════════════════════════════════════════════════ */

/** Switch the active dashboard section. */
function switchSection(sectionName) {
    // Hide all sections
    document.querySelectorAll('.section').forEach(s => s.classList.remove('active'));

    // Deactivate all nav items
    document.querySelectorAll('.nav-item').forEach(n => n.classList.remove('active'));

    // Activate the target section
    const target = document.getElementById(`section-${sectionName}`);
    if (target) {
        target.classList.add('active');
        // Re-trigger animation
        target.style.animation = 'none';
        target.offsetHeight; // Force reflow
        target.style.animation = '';
    }

    // Activate the corresponding nav button
    const navBtn = document.querySelector(`.nav-item[data-section="${sectionName}"]`);
    if (navBtn) navBtn.classList.add('active');

    // Refresh data when switching to data-heavy sections
    if (sectionName === 'dashboard') refreshDashboard();
    if (sectionName === 'all') renderAllStudents();
}

// Bind nav buttons
document.querySelectorAll('.nav-item[data-section]').forEach(btn => {
    btn.addEventListener('click', () => {
        switchSection(btn.dataset.section);
    });
});

/* ══════════════════════════════════════════════════════════════
   TOAST NOTIFICATIONS
   ══════════════════════════════════════════════════════════════ */

const TOAST_ICONS = {
    success: `<svg class="toast-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M22 11.08V12a10 10 0 1 1-5.93-9.14"/><polyline points="22 4 12 14.01 9 11.01"/></svg>`,
    error:   `<svg class="toast-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><circle cx="12" cy="12" r="10"/><line x1="15" y1="9" x2="9" y2="15"/><line x1="9" y1="9" x2="15" y2="15"/></svg>`,
    info:    `<svg class="toast-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><circle cx="12" cy="12" r="10"/><line x1="12" y1="16" x2="12" y2="12"/><line x1="12" y1="8" x2="12.01" y2="8"/></svg>`,
    warning: `<svg class="toast-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M10.29 3.86L1.82 18a2 2 0 0 0 1.71 3h16.94a2 2 0 0 0 1.71-3L13.71 3.86a2 2 0 0 0-3.42 0z"/><line x1="12" y1="9" x2="12" y2="13"/><line x1="12" y1="17" x2="12.01" y2="17"/></svg>`
};

/**
 * Display a toast notification.
 * @param {string} message  — The notification text.
 * @param {'success'|'error'|'info'|'warning'} type — Toast type.
 * @param {number} duration — Auto-dismiss time in ms (default: 4000).
 */
function showToast(message, type = 'info', duration = 4000) {
    const container = document.getElementById('toast-container');
    if (!container) return;

    const toast = document.createElement('div');
    toast.className = `toast toast-${type}`;
    toast.innerHTML = `
        ${TOAST_ICONS[type] || TOAST_ICONS.info}
        <span class="toast-message">${message}</span>
        <button class="toast-close" onclick="this.parentElement.remove()">×</button>
    `;

    container.appendChild(toast);

    // Auto-dismiss
    setTimeout(() => {
        toast.classList.add('removing');
        setTimeout(() => toast.remove(), 300);
    }, duration);
}

/* ══════════════════════════════════════════════════════════════
   VALIDATION
   ══════════════════════════════════════════════════════════════ */

/** Check if email ends with @diu.edu.bd */
function isValidEmail(email) {
    return email.includes('@diu.edu.bd');
}

/** Check if contact has 7+ characters with only digits, +, - */
function isValidContact(contact) {
    if (contact.length < 7) return false;
    return /^[\d+\-]+$/.test(contact);
}

/**
 * Validate all fields for adding/editing a student.
 * @param {Object} student — { name, id, email, bg, cell }
 * @param {string|null} excludeId — ID to exclude from duplicate checks (for editing).
 * @returns {string|null} — Error message, or null if valid.
 */
function validateStudent(student, excludeId = null) {
    const students = getStudents();

    if (!student.name || student.name.trim().length < 2)
        return 'Name must be at least 2 characters.';

    if (!student.id || student.id.trim().length === 0)
        return 'Student ID is required.';

    if (students.some(s => s.id === student.id && s.id !== excludeId))
        return `Student ID "${student.id}" already exists.`;

    if (!isValidEmail(student.email))
        return 'Email must contain @diu.edu.bd';

    if (students.some(s => s.email === student.email && s.id !== excludeId))
        return `Email "${student.email}" is already registered.`;

    if (!student.bg)
        return 'Please select a blood group.';

    if (!isValidContact(student.cell))
        return 'Contact must be 7+ characters with digits, + and - only.';

    if (students.some(s => s.cell === student.cell && s.id !== excludeId))
        return `Contact "${student.cell}" is already registered.`;

    return null; // All valid
}

/* ══════════════════════════════════════════════════════════════
   ADD STUDENT
   ══════════════════════════════════════════════════════════════ */

const addForm = document.getElementById('add-student-form');
if (addForm) {
    addForm.addEventListener('submit', function(e) {
        e.preventDefault();

        const student = {
            name:  document.getElementById('input-name').value.trim(),
            id:    document.getElementById('input-id').value.trim(),
            email: document.getElementById('input-email').value.trim(),
            bg:    document.getElementById('input-blood').value,
            cell:  document.getElementById('input-contact').value.trim(),
            addedAt: new Date().toISOString()
        };

        const error = validateStudent(student);
        if (error) {
            showToast(error, 'error');
            return;
        }

        const students = getStudents();
        students.push(student);
        saveStudents(students);

        showToast(`Student "${student.name}" added successfully!`, 'success');
        addForm.reset();
        refreshDashboard();
    });
}

/* ══════════════════════════════════════════════════════════════
   SEARCH STUDENT
   ══════════════════════════════════════════════════════════════ */

// Handle Enter key in search input
const searchInput = document.getElementById('search-input');
if (searchInput) {
    searchInput.addEventListener('keypress', function(e) {
        if (e.key === 'Enter') searchStudent();
    });
}

function searchStudent() {
    const input = document.getElementById('search-input');
    const resultDiv = document.getElementById('search-result');
    if (!input || !resultDiv) return;

    const searchId = input.value.trim();
    if (!searchId) {
        showToast('Please enter a Student ID to search.', 'warning');
        return;
    }

    const students = getStudents();
    const found = students.find(s => s.id === searchId);

    resultDiv.style.display = 'block';

    if (found) {
        resultDiv.innerHTML = `
            <div class="result-card">
                <h3>✓ Student Found</h3>
                <div class="result-fields">
                    <div class="result-field">
                        <span class="field-label">Name</span>
                        <span class="field-value">${escapeHtml(found.name)}</span>
                    </div>
                    <div class="result-field">
                        <span class="field-label">Student ID</span>
                        <span class="field-value">${escapeHtml(found.id)}</span>
                    </div>
                    <div class="result-field">
                        <span class="field-label">Email</span>
                        <span class="field-value">${escapeHtml(found.email)}</span>
                    </div>
                    <div class="result-field">
                        <span class="field-label">Blood Group</span>
                        <span class="field-value"><span class="blood-badge">${escapeHtml(found.bg)}</span></span>
                    </div>
                    <div class="result-field" style="grid-column: 1/-1;">
                        <span class="field-label">Contact</span>
                        <span class="field-value">${escapeHtml(found.cell)}</span>
                    </div>
                </div>
            </div>
        `;
    } else {
        resultDiv.innerHTML = `
            <div class="result-not-found">
                <strong>No student found</strong> with ID "${escapeHtml(searchId)}"
            </div>
        `;
    }
}

/* ══════════════════════════════════════════════════════════════
   ALL STUDENTS TABLE
   ══════════════════════════════════════════════════════════════ */

function renderAllStudents(filterText = '') {
    const tbody = document.getElementById('all-students-body');
    if (!tbody) return;

    let students = getStudents();

    // Apply filter
    if (filterText) {
        const query = filterText.toLowerCase();
        students = students.filter(s =>
            s.name.toLowerCase().includes(query) ||
            s.id.toLowerCase().includes(query) ||
            s.email.toLowerCase().includes(query) ||
            s.bg.toLowerCase().includes(query) ||
            s.cell.includes(query)
        );
    }

    if (students.length === 0) {
        tbody.innerHTML = `
            <tr class="empty-row">
                <td colspan="7">${filterText ? 'No matching records found.' : 'No students in the database yet.'}</td>
            </tr>
        `;
        return;
    }

    tbody.innerHTML = students.map((s, i) => `
        <tr>
            <td>${i + 1}</td>
            <td>${escapeHtml(s.name)}</td>
            <td>${escapeHtml(s.id)}</td>
            <td>${escapeHtml(s.email)}</td>
            <td><span class="blood-badge">${escapeHtml(s.bg)}</span></td>
            <td>${escapeHtml(s.cell)}</td>
            <td>
                <div class="action-btns">
                    <button class="btn-icon btn-icon-edit" title="Edit" onclick="openEditModal('${escapeAttr(s.id)}')">
                        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M11 4H4a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2v-7"/><path d="M18.5 2.5a2.121 2.121 0 0 1 3 3L12 15l-4 1 1-4 9.5-9.5z"/></svg>
                    </button>
                    <button class="btn-icon btn-icon-delete" title="Delete" onclick="openDeleteModal('${escapeAttr(s.id)}')">
                        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><polyline points="3 6 5 6 21 6"/><path d="M19 6v14a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2V6m3 0V4a2 2 0 0 1 2-2h4a2 2 0 0 1 2 2v2"/></svg>
                    </button>
                </div>
            </td>
        </tr>
    `).join('');
}

function filterStudents() {
    const input = document.getElementById('filter-input');
    renderAllStudents(input ? input.value : '');
}

/* ══════════════════════════════════════════════════════════════
   EDIT STUDENT (Modal)
   ══════════════════════════════════════════════════════════════ */

function openEditModal(studentId) {
    const students = getStudents();
    const student = students.find(s => s.id === studentId);
    if (!student) {
        showToast('Student not found.', 'error');
        return;
    }

    document.getElementById('edit-original-id').value = student.id;
    document.getElementById('edit-name').value = student.name;
    document.getElementById('edit-id').value = student.id;
    document.getElementById('edit-email').value = student.email;
    document.getElementById('edit-blood').value = student.bg;
    document.getElementById('edit-contact').value = student.cell;

    document.getElementById('edit-modal').style.display = 'flex';
}

function closeModal() {
    document.getElementById('edit-modal').style.display = 'none';
}

const editForm = document.getElementById('edit-student-form');
if (editForm) {
    editForm.addEventListener('submit', function(e) {
        e.preventDefault();

        const originalId = document.getElementById('edit-original-id').value;
        const updated = {
            name:  document.getElementById('edit-name').value.trim(),
            id:    document.getElementById('edit-id').value.trim(),
            email: document.getElementById('edit-email').value.trim(),
            bg:    document.getElementById('edit-blood').value,
            cell:  document.getElementById('edit-contact').value.trim()
        };

        const error = validateStudent(updated, originalId);
        if (error) {
            showToast(error, 'error');
            return;
        }

        const students = getStudents();
        const index = students.findIndex(s => s.id === originalId);
        if (index === -1) {
            showToast('Student record not found.', 'error');
            return;
        }

        // Preserve addedAt timestamp
        updated.addedAt = students[index].addedAt;
        students[index] = updated;
        saveStudents(students);

        showToast(`Student "${updated.name}" updated successfully!`, 'success');
        closeModal();
        renderAllStudents();
        refreshDashboard();
    });
}

/* ══════════════════════════════════════════════════════════════
   DELETE STUDENT (Modal)
   ══════════════════════════════════════════════════════════════ */

let pendingDeleteId = null;

function openDeleteModal(studentId) {
    const students = getStudents();
    const student = students.find(s => s.id === studentId);
    if (!student) return;

    pendingDeleteId = studentId;
    document.getElementById('delete-student-name').textContent =
        `${student.name} (${student.id})`;
    document.getElementById('delete-modal').style.display = 'flex';
}

function closeDeleteModal() {
    pendingDeleteId = null;
    document.getElementById('delete-modal').style.display = 'none';
}

const confirmDeleteBtn = document.getElementById('btn-confirm-delete');
if (confirmDeleteBtn) {
    confirmDeleteBtn.addEventListener('click', function() {
        if (!pendingDeleteId) return;

        let students = getStudents();
        const student = students.find(s => s.id === pendingDeleteId);
        const name = student ? student.name : 'Unknown';

        students = students.filter(s => s.id !== pendingDeleteId);
        saveStudents(students);

        showToast(`Student "${name}" deleted.`, 'info');
        closeDeleteModal();
        renderAllStudents();
        refreshDashboard();
    });
}

/* ══════════════════════════════════════════════════════════════
   DASHBOARD STATS
   ══════════════════════════════════════════════════════════════ */

function refreshDashboard() {
    const students = getStudents();

    // Total count
    const totalEl = document.getElementById('total-count');
    if (totalEl) totalEl.textContent = students.length;

    // Added today
    const today = new Date().toISOString().split('T')[0];
    const addedToday = students.filter(s =>
        s.addedAt && s.addedAt.startsWith(today)
    ).length;
    const recentEl = document.getElementById('recent-count');
    if (recentEl) recentEl.textContent = addedToday;

    // Unique blood groups
    const uniqueGroups = new Set(students.map(s => s.bg)).size;
    const bloodEl = document.getElementById('blood-groups');
    if (bloodEl) bloodEl.textContent = uniqueGroups;

    // Storage status
    const storageEl = document.getElementById('storage-status');
    if (storageEl) storageEl.textContent = students.length > 0 ? 'Active' : 'Empty';

    // Recent students table (last 5)
    renderRecentTable(students);
}

function renderRecentTable(students) {
    const tbody = document.getElementById('recent-table-body');
    if (!tbody) return;

    const recent = students.slice(-5).reverse();

    if (recent.length === 0) {
        tbody.innerHTML = `
            <tr class="empty-row">
                <td colspan="6">No students in the database yet. Add one to get started!</td>
            </tr>
        `;
        return;
    }

    tbody.innerHTML = recent.map((s, i) => `
        <tr>
            <td>${i + 1}</td>
            <td>${escapeHtml(s.name)}</td>
            <td>${escapeHtml(s.id)}</td>
            <td>${escapeHtml(s.email)}</td>
            <td><span class="blood-badge">${escapeHtml(s.bg)}</span></td>
            <td>${escapeHtml(s.cell)}</td>
        </tr>
    `).join('');
}

/* ══════════════════════════════════════════════════════════════
   UTILITY FUNCTIONS
   ══════════════════════════════════════════════════════════════ */

/** Escape HTML special characters to prevent XSS. */
function escapeHtml(text) {
    if (!text) return '';
    const map = { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#039;' };
    return text.replace(/[&<>"']/g, c => map[c]);
}

/** Escape for use inside HTML attribute strings. */
function escapeAttr(text) {
    return text.replace(/'/g, "\\'").replace(/"/g, '&quot;');
}

/* ══════════════════════════════════════════════════════════════
   INITIALIZATION
   ══════════════════════════════════════════════════════════════ */

document.addEventListener('DOMContentLoaded', function() {
    refreshDashboard();
    renderAllStudents();
});
