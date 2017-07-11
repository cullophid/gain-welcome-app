external resolvePromise : Js.Promise.t 'a => ('a => unit) => ('err => unit) => unit =
  "then" [@@bs.send];

type handler 'a = 'a => unit;

type t 'err 'ok = handler 'err => handler 'ok => unit;

let make create fail success => create fail success;

let succeed x => make (fun _ success => success x);

let fail x => make (fun fail _ => fail x);

let fork fail success task => task fail success;

let map f task => make (fun fail success => task fail (fun x => f x |> success));

let chain f task => make (fun fail success => task fail (fun x => (f x) fail success));

let biMap mapFail mapSuccess task =>
  make (
    fun fail success => task (fun err => mapFail err |> fail) (fun ok => mapSuccess ok |> success)
  );

let fold mapFail mapSuccess task =>
  make (
    fun _ success => task (fun err => mapFail err |> success) (fun ok => mapSuccess ok |> success)
  );

let fromLazyPromise f => make (fun fail success => resolvePromise (f ()) success fail);

let fromOption err opt =>
  switch opt {
  | None => fail err
  | Some x => succeed x
  };

let fromResult res =>
  switch res {
  | Result.Error err => fail err
  | Result.Ok v => succeed v
  };
