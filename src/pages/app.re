let component = ReasonReact.statefulComponent "App";

let make
    init::(init: Data.model)
    update::(update: Data.action => Data.model => (Data.model, Eff.t))
    render::(
      render: Data.model => (Data.action => unit) => ReasonReact.reactElement
    )
    _ => {
  ...component,
  initialState: fun () => (init, fun _ => ()),
  didMount: fun self => {
    let replaceState nextState =>
      self.update (fun state _ => ReasonReact.Update state) nextState;

    let rec dispatch a => {

      Js.log2 "Action " (a |> Data.printAction);

      let (state, _) = self.state;
      let (nextState, eff) = update a state;

      Js.log2 "State" (nextState |> Data.modelEncoder);

      replaceState (nextState, dispatch);

      switch eff {
        | None => ()
        | Some task => Task.fork dispatch dispatch task
      };
    };
    
    ReasonReact.Update (init, dispatch)
  },
  render: fun self => {
    let (state, dispatch) = self.state;
    render state dispatch
  }
};
