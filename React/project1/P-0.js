let itemCount = 0;
let uncheckedCount = 0;
const list = document.getElementById('todo-list');
const itemCountSpan = document.getElementById('item-count');
const uncheckedCountSpan = document.getElementById('unchecked-count');

function renderCounters() {
  uncheckedCountSpan.innerHTML = uncheckedCount;
  itemCountSpan.innerHTML = itemCount;
}

function addTodo(todo) {
  itemCount += 1;

let itemCount = 0;
let uncheckedCount = 0;
const list = document.getElementById('todo-list');
const itemCountSpan = document.getElementById('item-count');
const uncheckedCountSpan = document.getElementById('unchecked-count');

function renderCounters() {
  uncheckedCountSpan.innerHTML = uncheckedCount;
  itemCountSpan.innerHTML = itemCount;
}

function addTodo(todo) {
  itemCount += 1;

// Create list item
  const li = document.createElement('li');

// Create checkbox inside list item
  const input = document.createElement('input');
  input.setAttribute('type', 'checkbox');

