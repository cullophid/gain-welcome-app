open Data;
let component = ReasonReact.statefulComponent "App";

let make
    init::(init: Model.t)
    update::(update: Action.t => Model.t => (Model.t , option (Task.t Action.t Action.t)))
    render::(
      render: Model.t  => (Action.t => unit) => ReasonReact.reactElement
    )
    _ => {
  ...component,
  initialState: fun () => (init, fun a => Js.log2 "Default dispatch" a),
  didMount: fun self => {
    let replaceState state dispatch => {
      self.update (fun componentState _ => ReasonReact.Update componentState) (state, dispatch);
    };
    let dispatch = StartApp.make
      ::init
      ::update
      render::replaceState
     ;
     ReasonReact.Update (init, dispatch)

  },
  render: fun self => {
    let (state, dispatch) = self.state;
    Js.log2 "State" (state |> Model.encoder);
    render state dispatch
  }
};
