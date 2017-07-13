type dispatch 'action = 'action => unit;

let make ::init ::update ::render => {
  let state = ref init;
  let rec dispatch a => {
    Js.log2 "ACTION" a;
    let (nextState, eff) = update a !state;
    state := nextState;
    render !state dispatch;
    switch eff {
    | None => ()
    | Some t => Task.fork dispatch dispatch t
    }
  };

  render !state dispatch;
  dispatch;

}

