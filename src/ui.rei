open ReactNative;

type styledView = style::(list Style.t)? => list ReasonReact.reactElement => ReasonReact.reactElement;
type styledText = style::(list Style.t)? => string => ReasonReact.reactElement;

let view : styledView;

let text : style::(list Style.t)? => size::[`small | `default | `large]? => string => ReasonReact.reactElement;

let paragraph : styledText;

let image : blurRadius::float? => style::(list Style.t)? => Image.imageSource => ReasonReact.reactElement;

let row : 
   style::(list Style.t)? => 
   justifyContent::([ |`flexStart | `center | `flexEnd | `spaceAround | `spaceBetween | `stretch])? => 
   alignItems::([ |`baseline  | `center | `flexEnd |`flexStart | `stretch])? => 
   list ReasonReact.reactElement => ReasonReact.reactElement;

let column : 
   style::(list Style.t)? => 
   justifyContent::([ |`flexStart | `center | `flexEnd | `spaceAround | `spaceBetween | `stretch])? => 
   alignItems::([ |`baseline  | `center | `flexEnd |`flexStart | `stretch])? => 
   list ReasonReact.reactElement => ReasonReact.reactElement;

let padding : styledView;

let backgroundImage : blurRadius::float? => ReactNative.Image.imageSource => ReasonReact.reactElement;

let statusBar : barStyle::[ |`lightContent | `darkContent | `default] => ReasonReact.reactElement;

let label: styledText;

let inputGroup : styledView;

let textInput :
  inputRef::(Js.null ReasonReact.reactRef => unit)? =>
  autoCapitalize::[< `characters | `none | `sentences | `words > `sentences ]? =>
  style::(list Style.t)? =>
  keyboardType::[ `asciiCapable | `decimalPad | `default | `emailAddress | `namePhonePad | `numberPad | `numbersAndPunctuation | `numeric | `phonePad | `twitter | `url | `webSearch ]? =>
  secureTextEntry:: bool? =>
  onSubmitEditing::(unit => unit)? =>
  returnKeyType::[ `default | `done_ | `emergencyCall | `go | `google | `join | `next | `none | `previous | `route | `search | `send | `yahoo ]? =>
  onChangeText::(string => unit) =>
  string => 
  ReasonReact.reactElement;

let touchable : 
  accessibilityTraits::(list [ `adjustable | `allowsDirectInteraction | `button | `disabled | `frequentUpdates | `header | `image | `key | `link | `none | `pageTurn | `plays | `search | `selected | `startsMedia | `summary | `text ])? => 
  onPress::(unit => unit) => 
  list ReasonReact.reactElement => 
  ReasonReact.reactElement; 

let button : style::(list Style.t)? => theme::[> `danger | `default | `info | `primary | `success | `warning ]? => onPress:: (unit => unit) => list ReasonReact.reactElement => ReasonReact.reactElement;

let buttonSpinner : style::(list Style.t)? => remote::Remote.t _ 'a => string => ReasonReact.reactElement;

let alert : style::(list Style.t)? => theme::[> `danger | `default | `info | `primary | `success | `warning ]? => string => ReasonReact.reactElement;

let activityIndicator : ReasonReact.reactElement;

let media : styledView;

let mediaLeft : styledView;

let mediaRight : styledView;

let mediaBody : styledView;

type iconType = [ |`arrow_forward | `tag_faces | `tag_faces_large];

let icon : style::(list Style.t)? => tintColor::string? => iconType => ReasonReact.reactElement;


let choice : onPress::(unit => unit) => left::ReasonReact.reactElement? => right::ReasonReact.reactElement? => list ReasonReact.reactElement => ReasonReact.reactElement;