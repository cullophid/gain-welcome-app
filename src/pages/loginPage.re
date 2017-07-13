open ReactNative;
type state = {passwordRef: option ReasonReact.reactRef};
let setPasswordRef theRef _ => ReasonReact.SilentUpdate {passwordRef: Js.Null.to_opt theRef};
let component = ReasonReact.statefulComponent "LoginPage";

let make ::dispatch ::loginForm ::session _ =>  {
  {
    ...component,
    initialState: fun () => {passwordRef: None },
    render: fun self => {
      open Ui;
      open Data.Action;
      open Data.LoginForm;
      let submit _ => Login loginForm |> dispatch;
      let focus ref => switch ref {
        | Some r => (ReasonReact.refToJsObj r)##focus ();
        | None  => ()
      };
      column justifyContent::`center alignItems::`center [
        statusBar barStyle::`lightContent,
        backgroundImage (Image.Required (Packager.require "../../../../img/img-25-dark.jpg")),
        view style::[Style.(style [widthPct 80.0])] [
          inputGroup [
            label "Email",
            textInput
              autoCapitalize::`none
              keyboardType::`emailAddress
              onChangeText::(fun email => dispatch (UpdateLoginForm {...loginForm, email}))
              onSubmitEditing::(fun _ => focus self.state.passwordRef)
              loginForm.email
          ],
          inputGroup [
            label "Password",
            textInput
              inputRef::(self.update setPasswordRef)
              autoCapitalize::`none
              secureTextEntry::true
              keyboardType::`default
              onChangeText::(fun password => dispatch (UpdateLoginForm {...loginForm, password}))
              onSubmitEditing::submit
              loginForm.password
          ],
          button onPress::submit theme::`success [
           buttonSpinner remote::session "Go"
          ]
        ],
          padding [
          {switch session {
          | Remote.Error err => alert theme::`danger err
          | _ => ReasonReact.nullElement
          }}
        ]
      ]
    }
  };
};


  
  /*

   
       
          button onPress::submit theme::`success [
            text style::Style.(style [color "white"]) "Go"
          ]
        ]
  
        
          


  padding [
          {switch session {
          | Remote.Error err => <Alert message=err theme=`danger />
          | Remote.Pending => <ActivityIndicator  size=`large />
          | _ => ReasonReact.nullElement
          }}
        ]
  */