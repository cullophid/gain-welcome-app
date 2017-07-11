open Data;
type state = {
  mobileRef: option ReasonReact.reactRef,
  concentRef: option ReasonReact.reactRef
};
let setMobileRef theRef {ReasonReact.state} => ReasonReact.SilentUpdate {...state, mobileRef: Js.Null.to_opt theRef};
let setConcnetRef theRef {ReasonReact.state} => ReasonReact.SilentUpdate {...state, concentRef: Js.Null.to_opt theRef};
let component = ReasonReact.statefulComponent "VisitorDetailsPage";
let make ::dispatch ::visitorForm _ =>  {
  {
    ...component,
    initialState: fun () => {mobileRef: None, concentRef: None },
    render: fun self => {
      open Components;
      let submit _ => SubmitVisitorForm visitorForm |> dispatch;
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
            <Label value="Name" />
            <Input
              autoCapitalize=`none
              keyboardType=`default
              onChange=(fun name => dispatch (UpdateVisitorForm {...visitorForm, name}))
              onSubmit=(fun _ => focus self.state.mobileRef)
              value=visitorForm.name
            />
          </InputGroup>
          <InputGroup>
            <Label value="Mobile" />
            <Input
              inputRef=(self.update setMobileRef)
              autoCapitalize=`none
              keyboardType=`decimalPad
              onChange=(fun mobile => dispatch (UpdateVisitorForm {...visitorForm, mobile}))
              value=visitorForm.mobile
              onSubmit=(submit)
            />
          </InputGroup>
          <Btn onPress=submit theme=`success> <Text value="Sæt mig i kø" style=Style.(style [color "white"]) /> </Btn>
        </View>
      </Column>
    }
  }
  };
