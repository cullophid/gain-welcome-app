open ReactNative;
let component = ReasonReact.statelessComponent "ThankYou";
let stylesheet = {
  open Style;
  StyleSheet.create {
    "wrapper": style [
      Style.widthPct 80.0
    ]
  };
};
let render visitor dispatch => {
  open Ui;
  open Data.Action;
  open Data.Visitor;
  let {name, mobile} = visitor;
  let position = string_of_int visitor.position;
  column alignItems::`center justifyContent::`center [
    statusBar barStyle::`lightContent,
    backgroundImage (Image.Required (Packager.require "../../../../img/img-25-dark.jpg")),
    padding style::[stylesheet##wrapper] [
      text size::`large ({j|Tak $(name)|j}),
      paragraph ({j|Du er nummer $(position) i køen. Vi har sent en SMS til $(mobile) med mere information|j}),
      padding [
        row justifyContent::`center alignItems::`center [
          icon tintColor::"white" `tag_faces_large
        ]
      ],
      button theme::`success onPress::(fun () => dispatch Reset) [
        text {j|Næste besøgende|j}
      ]
    ]
  ]
};
let make ::dispatch ::visitor _ =>  {
  {
    ...component,
    render: fun _ => {
      switch visitor {
      | Remote.Ready v => render v dispatch
      | _ => Ui.alert "Visitor is not ready"
      }
    }
  }
};
