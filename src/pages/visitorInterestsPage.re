open Data;
open Components;
let component = ReasonReact.statelessComponent "VisitorInterests";
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

let make ::dispatch _ =>  {
  {
    ...component,
    render: fun _ => {
      let select t () => dispatch (SelectVisitorInterests t);
      <Column justifyContent=`center alignItems=`center>
        <StatusBar barStyle=`lightContent />
        <BackgroundImage
          source=(Image.Required (Packager.require "../../../../img/img-25-dark.jpg"))
        />
        <View style=stylesheet##wrapper>
          <Padding>
            <Text value="Da vores sælgere ofte er optaget, kan du vælge at få hjælp af andet personale til for eksempel en prøvekørsel. 
            Vælg den af de følgende muligheder der bedst passer til dit formål med besøget hos os." />
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Browsing) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="A" /> 
              <Text value="Se og røre" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Learn) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="B" /> 
              <Text value="Lære mere" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Testdrive) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="C" /> 
              <Text value="Prøvetur" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Financing) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="D" /> 
              <Text value="Financiering" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
          <Padding>
            <TouchableOpacity onPress=(select Buy) >
            <Row style=stylesheet##jumboButton  justifyContent=`spaceBetween alignItems=`center>
              <Text value="E" /> 
              <Text value="Købe" /> 
              <Text value=">"/>
            </Row>
            </TouchableOpacity>
          </Padding>
        </View>
      </Column>
    }
  }
};
