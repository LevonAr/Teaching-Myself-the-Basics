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
