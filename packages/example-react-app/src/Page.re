let component = ReasonReact.statelessComponent("Page");

let handleClick = (_event, _self) => Js.log("clicked!");

let query = {|
query getGengar {
  pokemon(name: "Gengar") {
    name
    attacks {
      fast {
        name
      }
    }
  }
}
|};

[@bs.module]
external gql : [@bs] (string => ReasonApolloClient.ApolloClient.documentNode) =
  "graphql-tag";

let componentMake = (~data: Js.Json.t, _children) => {
  ...component,
  render: self => {
    Js.log(data);
    <div onClick=(self.handle(handleClick))> (ReasonReact.stringToElement("rendered")) </div>
  }
};

let make = ReasonReactApollo.Graphql.make(~documentNode=([@bs] gql(query)), ~component, ~make=componentMake, ());


