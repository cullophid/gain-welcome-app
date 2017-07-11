open ReactNative;

let _style = Style.style [];

module StyleSheet = StyleSheet;
module Style = Style;
module View = View;
module StatusBar = StatusBar;
module Image = Image;
module Packager = Packager;
module ActivityIndicator = ActivityIndicator;
module TouchableOpacity = TouchableOpacity;


/*const _shadow = (width:number, height:number, shadowRadius:number, shadowColor:string, shadowOpacity:number) =>
  ({shadowOffset:{width, height}, shadowRadius, shadowColor, shadowOpacity})*/

let shadow i => {
  open Style;
  switch Platform.os {
    | IOS => [shadowOffset height::0.0 width::(0.7 *. i), shadowRadius (0.7 *. i), shadowColor "black", shadowOpacity 0.3]
    | Android => [elevation i]
  };
};
let stylesheet =
  Style.(
    StyleSheet.create {
      "text": style [
        fontSize 15.0,
        color "white",
        backgroundColor "transparent"
      ],
      "button":
        style [
          borderColor "#f0f0f0",
          borderWidth 1.0,
          borderRadius 3.0,
          padding 10.0,
          backgroundColor "transparent",
          alignItems `center,
          justifyContent `center,
          ...(shadow 5.0)
        ],
      "buttonSuccess": style [
        backgroundColor Theme.success,
        borderColor "transparent"
      ],
      "label": style [
        fontSize 15.0,
        color Theme.success,
        backgroundColor "transparent"
      ],
      "textInput":
        style [
          backgroundColor "transparent",
          borderWidth 0.0,
          height 28.0,
          padding 0.0,
          color "white",
          fontSize 15.0
        ],
      "textInputWrap": style [borderColor "#f0f0f0", borderBottomWidth 1.0],
      "inputGroup": style [
        marginBottom 15.0
      ],
      "row": style [flexDirection `row, flexGrow 1.0],
      "column": style [flexDirection `column, flexGrow 1.0],
      "padding": style [padding 15.0],
      "backgroundImage":
        style [
          left 0.0,
          top 0.0,
          position `absolute,
          widthPct 100.0,
          heightPct 100.0,
          overflow `hidden
        ],
      "backgroundImageWrapper": style [position `absolute, widthPct 100.0, heightPct 100.0],
      "alert" : style [
        borderRadius 2.0,
        padding 15.0,
        ...(shadow 10.0)
      ],
      "alertText" : style [
        color "white",
        backgroundColor "transparent"
      ],
      "alertInfo" : style [ backgroundColor Theme.info ],
      "alertWarning" : style [ backgroundColor Theme.warning ],
      "alertDanger" : style [ backgroundColor Theme.danger ]
      
    }
  );




module Text = {
  let component = ReasonReact.statelessComponent "Text";
  let make ::value ::style=_style _children => {
  let styles = StyleSheet.flatten [stylesheet##text, style];
    {
      ...component,
      render: fun _ => {
        ReasonReact.element (ReactNative.Text.make style::styles value::value _children)
      }
    }
  };
};

/* forms and input */
module Btn = {
  let component = ReasonReact.statelessComponent "Btn";
  let make ::style=_style ::onPress ::theme=`default children => {
    ...component,
    render: fun _ => {
      let styles = StyleSheet.flatten [
          stylesheet##button, 
          (theme == `success ? stylesheet##buttonSuccess : _style),
          style
        ];
      <TouchableOpacity accessibilityTraits=[`button] onPress>
        (ReasonReact.element (View.make style::styles children))
      </TouchableOpacity>
    }
  };
};

module Label = {
  let component = ReasonReact.statelessComponent "Label";
  let make ::value ::style=_style _ => {
    {
      ...component,
      render: fun _ => {
        let styles = StyleSheet.flatten [stylesheet##label, style];
        <Text style=styles value=value />
      }
    }
  }
};

module InputGroup = {
  let component= ReasonReact.statelessComponent "InputGroup";
  let make ::style=_style children =>
    {
      ...component,
      render: fun _ => {
        let styles = StyleSheet.flatten [
          stylesheet##inputGroup,
          style
        ];
        ReasonReact.element (View.make style::styles children)
      }
    };
};

module Input = {
  let component = ReasonReact.statelessComponent "Input";
  let make
      ::inputRef=(fun _ => ())
      ::autoCapitalize=`sentences
      ::style=(Style.style [])
      ::keyboardType=`default
      ::secure=false
      ::onChange
      ::onSubmit=(fun _ => ())
      ::returnKeyType=`next
      ::value
      _ => {
    ...component,
    render: fun _ => {
      let styles = StyleSheet.flatten [stylesheet##textInput, style];
      <View style=stylesheet##textInputWrap>
        <TextInput
          ref=inputRef
          autoCapitalize
          keyboardType
          style=styles
          secureTextEntry=secure
          onChangeText=onChange
          onSubmitEditing=onSubmit
          returnKeyType
          underlineColorAndroid="transparent"
          value
        />
      </View>
    }
  };
};

/* Layout */
module Row = {
  let component = ReasonReact.statelessComponent "Row";
  let make ::justifyContent=`flexStart ::alignItems=`flexStart ::style=(Style.style []) children => {
    ...component,
    render: fun _ => {
      let styles =
        StyleSheet.flatten [
          stylesheet##column,
          Style.style [Style.justifyContent justifyContent],
          Style.style [Style.alignItems alignItems],
          style
        ];
      ReasonReact.element (View.make style::styles children)
    }
  };
};

module Column = {
  let component = ReasonReact.statelessComponent "Column";
  let make ::justifyContent=`flexStart ::alignItems=`flexStart ::style=(Style.style []) children => {
    ...component,
    render: fun _ => {
      let styles =
        StyleSheet.flatten [
          stylesheet##column,
          Style.style [Style.justifyContent justifyContent],
          Style.style [Style.alignItems alignItems],
          style
        ];
      ReasonReact.element (View.make style::styles children)
    }
  };
};

module Padding = {
  let component = ReasonReact.statelessComponent "Padding";
  let make ::style=_style children => {
    ...component,
    render: fun _ => {
      let styles = StyleSheet.flatten [stylesheet##padding, style];
      ReasonReact.element (View.make style::styles children)
    }
  };
};

/* Img */
module BackgroundImage = {
  let component = ReasonReact.statelessComponent "BackgroundImage";
  let make ::source ::blur=0.0 _ => {
    ...component,
    render: fun _ =>
      <View style=stylesheet##backgroundImageWrapper>
        <Image source style=stylesheet##backgroundImage blurRadius=blur />
      </View>
  };
};

module Alert = {
  let component  = ReasonReact.statelessComponent "Alert";
  let make ::style=_style ::theme=`info ::message _ => {
    {
      ...component,
      render: fun _ => {
        let styles = StyleSheet.flatten [
          stylesheet##alert,
          (theme == `info ? stylesheet##alertInfo : _style),
          (theme == `warning ? stylesheet##alertWarning : _style),
          (theme == `danger ? stylesheet##alertDanger : _style),
          style
        ];
        <View style=styles> <Text style=stylesheet##alertText value=message /> </View>

      }
    }
  };
};