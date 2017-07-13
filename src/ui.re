open ReactNative;
type styledView = style::(list Style.t)? => list ReasonReact.reactElement => ReasonReact.reactElement;
type styledText = style::(list Style.t)? => string => ReasonReact.reactElement;
let imgFolder = "../../../img/";
let _style = Style.style [];

let shadow i =>
  Style.(
    switch Platform.os {
    | IOS => [
        shadowOffset height::0.0 width::(0.7 *. i),
        shadowRadius (0.7 *. i),
        shadowColor "black",
        shadowOpacity 0.3
      ]
    | Android => [elevation i]
    }
  );

let stylesheet = {
  open Style;
  StyleSheet.create {
    "text": style [
      fontSize 12.0, 
      color "white", 
      backgroundColor "transparent"
      ],
    "textSmall": style [fontSize 10.0],
    "textLarge": style [fontSize 18.0],
    "paragraph": style [ marginBottom 15.0],
    "button":
      style [
        borderColor "#f0f0f0",
        borderWidth 1.0,
        borderRadius 3.0,
        padding 10.0,
        backgroundColor "transparent",
        alignItems `center,
        justifyContent `center,
        ...shadow 5.0
      ],
    "buttonPrimary": style [backgroundColor Theme.primary, borderColor "transparent"],
    "buttonSuccess": style [backgroundColor Theme.success, borderColor "transparent"],
    "buttonInfo": style [backgroundColor Theme.info, borderColor "transparent"],
    "buttonWarning": style [backgroundColor Theme.warning, borderColor "transparent"],
    "buttonDanger": style [backgroundColor Theme.danger, borderColor "transparent"],
    "label": style [fontSize 15.0, color Theme.success, backgroundColor "transparent"],
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
    "inputGroup": style [marginBottom 15.0, widthPct 100.0],
    "row": style [flexDirection `row, flexGrow 1.0],
    "column": style [flexDirection `column, flexGrow 1.0],
    "padding": style [padding 15.0, widthPct 100.0],
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
    "alert": style [borderRadius 2.0, padding 15.0, ...shadow 10.0],
    "alertText": style [color "white", backgroundColor "transparent"],
    "alertInfo": style [backgroundColor Theme.info],
    "alertWarning": style [backgroundColor Theme.warning],
    "alertDanger": style [backgroundColor Theme.danger],
    "icon": style [],
    "media": style [ flexDirection `row ],
    "mediaLeft": style [ flex 0.0, marginRight 15.0 ],
    "mediaRight": style [ flex 0.0, marginLeft 15.0 ],
    "mediaBody": style [ flex 1.0 ],
     "choice": style [
        padding 15.0,
        marginBottom 15.0,
        backgroundColor "rgba(0, 0, 0, 0.5)",
        borderWidth 1.0,
        borderColor "white",
        ...(shadow 5.0)
      ]
  };
};

let view ::style=[] children => 
  ReasonReact.element @@ View.make style::(StyleSheet.flatten style) @@ Array.of_list children;

let text ::style=[] ::size=`default value => {
  let styles = {
    StyleSheet.flatten [
      stylesheet##text, 
      (size == `small ? stylesheet##textSmall : _style),
      (size == `large ? stylesheet##textLarge : _style),
      ...style
      ]
  };
  ReasonReact.element @@ Text.make style::styles ::value [||];
};

let paragraph ::style=[] value =>
  text style::[stylesheet##paragraph, ...style] value;


let image ::blurRadius=0.0 ::style=[] source =>
  ReasonReact.element @@ Image.make ::blurRadius style::(StyleSheet.flatten style) ::source [||];

let row ::style=[] ::justifyContent=`flexStart ::alignItems=`flexStart children => {
  let styles = [
    stylesheet##row,
    Style.style [Style.justifyContent justifyContent],
    Style.style [Style.alignItems alignItems],
    ...style
  ];
  view style::styles children;
};

let column ::style=[] ::justifyContent=`flexStart ::alignItems=`flexStart children => {
  let styles = [
    stylesheet##column,
    Style.style [Style.justifyContent justifyContent],
    Style.style [Style.alignItems alignItems],
    ...style
  ];
  view style::styles children;
};

let padding ::style=[] children => 
  view style:: [stylesheet##padding, ...style] children;


let backgroundImage ::blurRadius=0.0 source =>
  image style::[stylesheet##backgroundImage] ::blurRadius source;

let statusBar ::barStyle =>
  ReasonReact.element @@ StatusBar.make ::barStyle [||];

let label ::style=[] value =>
  text style::[stylesheet##label, ...style] value;

let inputGroup ::style=[] children =>
  view style::[stylesheet##inputGroup, ...style] children;


let textInput
  ::inputRef=(fun _ => ())
  ::autoCapitalize=`sentences
  ::style=[]
  ::keyboardType=`default
  ::secureTextEntry=false
  ::onSubmitEditing=(fun _ => ())
  ::returnKeyType=`next
  ::onChangeText
  value
  => {
    view style::[stylesheet##textInputWrap] [
      ReasonReact.element ref::inputRef 
        @@ TextInput.make
          ::autoCapitalize
          ::keyboardType
          style::(StyleSheet.flatten [stylesheet##textInput, ...style])
          ::secureTextEntry
          ::onChangeText
          ::onSubmitEditing
          ::returnKeyType
          underlineColorAndroid::"transparent"
          ::value
          [||]
    ];
};
let activityIndicator =
  ReasonReact.element @@ ActivityIndicator.make color::"white" [||];

let touchable ::accessibilityTraits=[`button] ::onPress children =>
  ReasonReact.element @@ TouchableOpacity.make ::accessibilityTraits ::onPress @@ Array.of_list children;

let button ::style=[] ::theme=`default ::onPress children => {
  let styles = [
    stylesheet##button,
    theme == `primary ? stylesheet##buttonPrimary : _style,
    theme == `info ? stylesheet##buttonInfo : _style,
    theme == `success ? stylesheet##buttonSuccess : _style,
    theme == `warning ? stylesheet##buttonWarning : _style,
    theme == `danger ? stylesheet##buttonDanger : _style,
    ...style 
  ];
  touchable ::onPress [
    view style::styles children
  ];
};

let buttonSpinner ::style=[] ::remote value => 
  switch remote {
  | Remote.Pending => activityIndicator
  | _ => text ::style value
  };

let alert ::style=[] ::theme=`default message => {
  let styles = [
    stylesheet##alert,
    (theme == `warning ? stylesheet##alertWarning : _style),
    (theme == `danger ? stylesheet##alertDanger : _style),
    ...style
  ];
  view style::styles [
    text style::[stylesheet##alertText] message
  ];
};

let media ::style=[] children =>
  view style::[stylesheet##media, ...style] children;

let mediaLeft ::style=[] children =>
  view style::[stylesheet##mediaLeft, ...style] children;

let mediaRight ::style=[] children =>
  view style::[stylesheet##mediaRight, ...style] children;

let mediaBody ::style=[] children =>
  view style::[stylesheet##mediaBody, ...style] children;


type iconType = [ |`arrow_forward | `tag_faces | `tag_faces_large];
let iconSource i => {
  open Packager;
  switch i {
    |`arrow_forward => require @@ imgFolder ^ "arrow_forward.png"    
    |`tag_faces => require @@ imgFolder ^ "tag_faces.png" 
    |`tag_faces_large => require @@ imgFolder ^ "tag_faces_large.png" 
  };
};

let icon ::style=[] ::tintColor="black" i =>
  image style::[stylesheet##icon, Style.style [Style.tintColor tintColor], ...style] @@ Image.Required (iconSource i);

  let choice ::onPress ::left=? ::right=? children => {
  touchable ::onPress [
    media style::[stylesheet##choice] [
      mediaLeft [
        switch left {
        | None => ReasonReact.nullElement
        | Some elem => elem
        }
        ],
      mediaBody children,
      mediaRight [
        switch right {
        | None => icon tintColor::"white" `arrow_forward
        | Some elem => elem
        }
      ]
    ]
  ]
};