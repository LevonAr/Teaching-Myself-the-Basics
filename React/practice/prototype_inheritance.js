let f = function () 
{
   this.a = 1;
   this.b = 2;
}

let o = new f(); // {a: 1, b: 2}
