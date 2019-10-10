let uncheckedCount = 0;
const list = document.getElementById('todo-list');
const itemCountSpan = document.getElementById('item-count');

const itemCountSpan = document.getElementById('item-count');

function renderCounters() {
  uncheckedCountSpan.innerHTML = uncheckedCount;
}
