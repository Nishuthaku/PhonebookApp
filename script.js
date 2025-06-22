const form = document.getElementById("phonebookForm");
const contactList = document.getElementById("contactList");
const searchInput = document.getElementById("search");
const message = document.getElementById("message");
const clearAllBtn = document.getElementById("clearAll");

let contacts = JSON.parse(localStorage.getItem("contacts")) || [];

function showMessage(text) {
  message.textContent = text;
  message.classList.remove("hidden");
  setTimeout(() => {
    message.classList.add("hidden");
  }, 2000);
}

function renderContacts(data) {
  contactList.innerHTML = "";
  data.forEach((contact, index) => {
    const row = document.createElement("tr");
    const searchTerm = searchInput.value.toLowerCase();
    const nameCell = contact.name.toLowerCase().includes(searchTerm) ? `<td style="background: #d1f7c4">${contact.name}</td>` : `<td>${contact.name}</td>`;
    row.innerHTML = `
      ${nameCell}
      <td>${contact.phone}</td>
      <td><button class="delete-btn" onclick="deleteContact(${index})">Delete</button></td>
    `;
    contactList.appendChild(row);
  });
}

function deleteContact(index) {
  contacts.splice(index, 1);
  localStorage.setItem("contacts", JSON.stringify(contacts));
  renderContacts(contacts);
}

form.addEventListener("submit", function (e) {
  e.preventDefault();
  const name = document.getElementById("name").value.trim();
  const phone = document.getElementById("phone").value.trim();
  if (name && phone) {
    contacts.push({ name, phone });
    localStorage.setItem("contacts", JSON.stringify(contacts));
    renderContacts(contacts);
    form.reset();
    showMessage("Contact added successfully!");
  }
});

searchInput.addEventListener("input", function () {
  const searchTerm = this.value.toLowerCase();
  const filtered = contacts.filter(c => c.name.toLowerCase().includes(searchTerm));
  renderContacts(filtered);
});

clearAllBtn.addEventListener("click", function () {
  if (confirm("Are you sure you want to clear all contacts?")) {
    contacts = [];
    localStorage.removeItem("contacts");
    renderContacts(contacts);
  }
});

// Initial render
renderContacts(contacts);
