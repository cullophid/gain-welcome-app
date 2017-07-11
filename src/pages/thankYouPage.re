open Data;
open Components;
let component = ReasonReact.statelessComponent "ThankYou";
let stylesheet = {
  open Style;
    StyleSheet.create {
    "title": style [
      color "white"
    ],
    "wrapper": style [
      widthPct 80.0
    ],
    "jumboButton": style [
      borderWidth 3.0,
      borderColor "white"
    ]
  };
};

let make ::dispatch  _ =>  {
  {
    ...component,
    render: fun _ => {
      let select t () => dispatch (SelectVisitorType t);
      <Column justifyContent=`center alignItems=`center>
        <StatusBar barStyle=`lightContent />
        <BackgroundImage
          source=(Image.Required (Packager.require "../../../../img/img-25-dark.jpg"))
        />
        <View style=stylesheet##wrapper>
          <Text value="thank you" />
        </View>
      </Column>
    }
  }
  };
