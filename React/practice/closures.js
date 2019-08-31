function makeHelloFunction() {
  var message = 'Hello!'

  function sayHello() {
    console.log(message)
  }
  
  return sayHello
}
