  type t 'err 'ok =
    | NotAsked
    | Pending
    | Error 'err
    | Ready 'ok
    ;

  let encoder errEncoder valueEncoder value => {
    open Json.Encode;
    switch (value) {
    | NotAsked => string "NotAsked"
    | Pending => string "Pending"
    | Error err => errEncoder err
    | Ready v => valueEncoder v
    };
  };