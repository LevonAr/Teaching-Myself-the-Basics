const classNames = {
  TODO_ITEM: 'todo-container',
  TODO_CHECKBOX: 'todo-checkbox',
  TODO_TEXT: 'todo-text',
  TODO_DELETE: 'todo-delete',
}

const list = document.getElementById('todo-list')
const itemCountSpan = document.getElementById('item-count')
const uncheckedCountSpan = document.getElementById('unchecked-count')

const checkObject = document.getElementsByClassName("checkGrab");

var i = document.getElementsByClassName("checkGrab")[0];

console.log(i);


let checkcounter = 0;

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
  checkbox.setAttribute('class', 'checkGrab');
  checkbox.setAttribute('onchange', 'countChecks()');
  container.appendChild(checkbox);

  let input = document.createElement('input');
  input.setAttribute('type', 'text');
  container.appendChild(input);
  
  list.appendChild(container);
}

function countChecks()
{
  checkObject = document.getElementsByClassName('checkGrab');

  console.log(checkObject[0]);
}
  
  
