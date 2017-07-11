open Data;
open Components;
let component = ReasonReact.statelessComponent "Home";
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
          <Padding>
            <Text value="Kære kunde" />
            <Text value="Giv os lidt baggrundsviden så vi bedre kan betjæne dig" />
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Private) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="1" /> 
              <Text value="Jeg er privat kunde og køber eller leaser selv min næste bil" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select PrivateToBusiness) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="2" /> 
              <Text value="Jeg er privat kunde og skal skifte til firmabil" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Business) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="3" /> 
              <Text value="Jeg kører firmabil og skal vælge min næste firmabil" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Na) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="4" /> 
              <Text value="Jeg ønsker ikke at dele denne information" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="1" /> 
              <Text value="Jeg er privat kunde og køber eller leaser selv min næste bil" /> 
              <Text value=">"/>
            </Row>
          </Padding>
        </View>
      </Column>
    }
  }
  };
