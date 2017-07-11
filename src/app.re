let component = ReasonReact.statefulComponent "App";

let make
    init::(init: Data.model)
    update::(update: Data.action => Data.model => (Data.model, option (Task.t Data.action Data.action)))
    render::(
      render: Data.model => (Data.action => unit) => ReasonReact.reactElement
    )
    _ => {
  ...component,
  initialState: fun () => (init, fun a => Js.log2 "Default dispatch" a),
  didMount: fun self => {
    print_endline "DID_MOUNT";
    let replaceState state dispatch => {
      Js.log "REPLACE STATE";
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
    print_endline "RENDER";
    Js.log2 "State" (state |> Data.modelEncoder |> Js.Json.stringify);
    render state dispatch
  }
};
