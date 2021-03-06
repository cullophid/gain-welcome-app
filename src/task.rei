type handler 'a = 'a => unit;
type t 'err 'ok = handler 'err => handler 'ok => unit;
let make : (handler 'err => handler 'ok => unit) => t 'err 'ok;
let succeed : 'ok => t 'err 'ok;
let fail : 'err => t 'err 'ok;
let fork : handler 'err => handler 'a => t 'err 'a => unit;

let map : ('a => 'b) => t 'err 'a => t 'err 'b;

let chain : ('a => t 'err 'b) => t 'err 'a => t 'err 'b;

let biMap : ('err => 'err2) => ('ok => 'ok2) => t 'err 'ok => t 'err2 'ok2;
let fold : ('err => 'b) => ('a => 'b) => t 'err 'a => t 'err 'b;
let fromLazyPromise : (unit => Js.Promise.t 'ok) => t 'err 'ok; 
let fromOption: 'err => option 'ok => t 'err 'ok;
let fromResult: Result.t 'err 'ok => t 'err 'ok;