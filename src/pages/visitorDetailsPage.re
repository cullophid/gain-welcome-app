open ReactNative;
type state = {
  mobileRef: option ReasonReact.reactRef,
  concentRef: option ReasonReact.reactRef
};

let stylesheet = {
  open Style;
    StyleSheet.create {
    "wrapper": style [
      widthPct 80.0
    ]
  };
};
let setMobileRef theRef {ReasonReact.state} => ReasonReact.SilentUpdate {...state, mobileRef: Js.Null.to_opt theRef};
let setConcnetRef theRef {ReasonReact.state} => ReasonReact.SilentUpdate {...state, concentRef: Js.Null.to_opt theRef};
let component = ReasonReact.statefulComponent "VisitorDetailsPage";
let make ::dispatch ::visitorForm ::visitor _ =>  {
  open Ui;
  open Data.Action;
  {
    ...component,
    initialState: fun () => {mobileRef: None, concentRef: None },
    render: fun self => {
      let submit _ => SubmitVisitorForm visitorForm |> dispatch;
      let focus ref => switch ref {
        | Some r => (ReasonReact.refToJsObj r)##focus ();
        | None  => ()
      };

      column alignItems::`center justifyContent::`center [
        statusBar barStyle::`lightContent,
        backgroundImage (Image.Required (Packager.require "../../../../img/img-25-dark.jpg")),
        padding style::[stylesheet##wrapper] [
          paragraph "Text...",
          inputGroup [
            label "Name",
             textInput
              onChangeText::(fun name => dispatch (UpdateVisitorForm {...visitorForm, name}))
              onSubmitEditing::(fun _ => focus self.state.mobileRef)
              visitorForm.name
          ],
          inputGroup [
            label "Mobile",
            textInput
              inputRef::(self.update setMobileRef)
              keyboardType::`numberPad
              onChangeText::(fun mobile => dispatch (UpdateVisitorForm {...visitorForm, mobile}))
              onSubmitEditing::submit
              visitorForm.mobile
          ],
          button theme::`success onPress::submit [
            buttonSpinner remote::visitor {j|Sæt mig i kø|j}
          ],
          padding [
            {
              switch visitor {
              | Remote.Error err => alert theme::`danger err
              | _ => ReasonReact.nullElement
              }
            }
          ]
        ]
      ];
    }
  }
  };
