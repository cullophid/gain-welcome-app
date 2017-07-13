open Components;
let component = ReasonReact.statelessComponent "VisitorInterests";
let stylesheet = {
  open Style;
    StyleSheet.create {
    "headerText" : style [color Theme.success],
    "wrapper": style [
      widthPct 80.0
    ]
  };
};

let renderQueue setQueue (queue:Data.Queue.t) => {
  open Ui;
  choice onPress::(setQueue queue.id) left::(text size::`large queue.order) [
    text size::`large queue.name,
    text size::`small queue.description
  ];
};


let make ::dispatch ::queues _ =>  {
  open Ui;
  open Data.Action;
  let setQueue t () => dispatch (SetVisitorQueue t);
  {
    ...component,
    render: fun _ => {

      column alignItems::`center justifyContent::`center [
        statusBar barStyle::`lightContent,
        backgroundImage (Image.Required (Packager.require "../../../../img/img-25-dark.jpg")),
        padding style::[stylesheet##wrapper] [
          switch queues {
            | Remote.Pending => activityIndicator
            | Remote.Error err => alert theme::`danger err
            | Remote.NotAsked => text "NOT ASKED"
            | Remote.Ready queues => {
              view [
                paragraph style::[stylesheet##headerText] {j|Vælg den af de følgende muligheder der bedst passer til dit formål med besøget hos os.|j},
                ...(List.map (renderQueue setQueue) queues)
              ]
            }
          }
        ]
      ]
    }
  };
};

 