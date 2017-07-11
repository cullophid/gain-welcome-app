type t 'err 'ok = 
  | Error 'err
  | Ok 'ok
  ;

let map : ('a => 'b) => t 'err 'a => t 'err 'b;
let chain : ('a => t 'err 'b) => t 'err 'a => t 'err 'b;
let fromOption : 'err => option 'a => t 'err 'a;