const sayHello = (function () {
  var message = 'Hello!'
  function sayHello() {
    console.log(message)
  }
  return sayHello
})()

const counter = (function() {
  let count = 0