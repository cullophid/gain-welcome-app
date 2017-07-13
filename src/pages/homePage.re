open ReactNative;
let component = ReasonReact.statelessComponent "Home";
let stylesheet = {
  open Style;
  StyleSheet.create {
    "title": style [fontSize 28.0, color Theme.success, fontWeight `_600 ],
    "headerText" : style [color Theme.success],
    "wrapper": style [
      Style.widthPct 80.0
    ]
  };
};


let make ::dispatch  _ =>  {
  open Ui;
  open Data.Action;
  {
    ...component,
    render: fun _ => {
      let select t () => dispatch (SetVisitorType t);
      column alignItems::`center justifyContent::`center [
        statusBar barStyle::`lightContent,
        backgroundImage (Image.Required (Packager.require "../../../../img/img-29-dark.jpg")),
        padding style::[stylesheet##wrapper][
          paragraph style::[stylesheet##title, stylesheet##headerText] {j|Velkommen!|j},
          paragraph style::[stylesheet##headerText] {j|Giv os lidt baggrundsviden så vi bedre kan betjæne dig|j},
          choice onPress::(select Private) left::(text size::`large "1") [
            text {j|Jeg er privat kunde og køber eller leaser selv min næste bil|j} 
          ],
          choice onPress::(select Business) left::(text size::`large "2") [
            text {j|Jeg er privat kunde og skal skifte til firmabil|j}
          ],
          choice onPress::(select PrivateToBusiness) left::(text size::`large "3") [
            text {j|Jeg kører firmabil og vælge min næste firmabil|j}
          ],
          choice onPress::(select Na) left::(text size::`large "4") [
            text {j|Jeg ønsker ikke at dele denne information|j}
          ]
        ]
      ];
    }
  };
 };