const classNames = {
  TODO_ITEM: 'todo-container',
  TODO_CHECKBOX: 'todo-checkbox',
  TODO_TEXT: 'todo-text',
  TODO_DELETE: 'todo-delete',
}

const list = document.getElementById('todo-list')
const itemCountSpan = document.getElementById('item-count')
const uncheckedCountSpan = document.getElementById('unchecked-count')

function newTodo() {
  if (typeof v !== 'undefined') 
  {
    v++;  
  } 
  
  else
  {
    v=1;
  }

  
  let container = document.createElement('div');
  
  let checkbox = document.createElement('input');
  checkbox.setAttribute('type', 'checkbox');
  container.appendChild(checkbox);

  let input = document.createElement('input');
  input.setAttribute('type', 'text');
  container.appendChild(input);

}
  
  
