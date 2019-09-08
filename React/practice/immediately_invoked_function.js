// this creates the same closure as in 1-closureExample.js, but doesn't pollute
// the global scope with a function called makeHelloFunction like that example
const sayHello = (function () {
  var message = 'Hello!'
  function sayHello() {
    console.log(message)
  }
  return sayHello
})()
