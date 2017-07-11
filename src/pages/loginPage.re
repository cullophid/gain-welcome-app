open Data;
type state = {passwordRef: option ReasonReact.reactRef};
let setPasswordRef theRef _ => ReasonReact.SilentUpdate {passwordRef: Js.Null.to_opt theRef};
let component = ReasonReact.statefulComponent "LoginPage";
let make ::dispatch ::loginForm ::session _ =>  {
  {
    ...component,
    initialState: fun () => {passwordRef: None },
    render: fun self => {
      open Components;
      let submit _ => Login loginForm |> dispatch;
      let focus ref => switch ref {
        | Some r => (ReasonReact.refToJsObj r)##focus ();
        | None  => ()
      };

      <Column justifyContent=`center alignItems=`center>
        <StatusBar barStyle=`lightContent />
        <BackgroundImage
          source=(Image.Required (Packager.require "../../../../img/img-25-dark.jpg"))
        />
        <View style=Style.(style [widthPct 80.0])>
          <InputGroup>
            <Label value="Email" />
            <Input
              autoCapitalize=`none
              keyboardType=`emailAddress
              onChange=(fun email => dispatch (UpdateLoginForm {...loginForm, email}))
              onSubmit=(fun _ => focus self.state.passwordRef)
              value=loginForm.email
            />
          </InputGroup>
          <InputGroup>
            <Label value="Password" />
            <Input
              inputRef=(self.update setPasswordRef)
              autoCapitalize=`none
              secure=true
              keyboardType=`default
              onChange=(fun password => dispatch (UpdateLoginForm {...loginForm, password}))
              value=loginForm.password
              onSubmit=submit
            />
          </InputGroup>
          <Btn onPress=submit theme=`success> <Text value="Go" style=Style.(style [color "white"]) /> </Btn>
        </View>
        <Padding>
          {switch session {
          | Remote.Error err => <Alert message=err theme=`danger />
          | Remote.Pending => <ActivityIndicator  size=`large />
          | _ => ReasonReact.nullElement
          }}
        </Padding>
      </Column>
    }
  }
  };
