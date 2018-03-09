open ReasonApolloClient;

open ReasonReactApollo;

let component = ReasonReact.statelessComponent("Page");

let handleClick = (_event, _self) => Js.log("clicked!");

module GengarQuery = [%graphql
  {|
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
  |}
];

[@bs.module] external gql : [@bs] (string => ApolloClient.documentNode) = "graphql-tag";

let componentMake = (~data: GengarQuery.t, ~apolloStatus: Graphql.apolloStatus, _children) => {
  ...component,
  render: _self =>
    if (apolloStatus.loading) {
      <div> (ReasonReact.stringToElement("loading...")) </div>;
    } else {
      Js.log(data);
      <div>
        (
          ReasonReact.stringToElement(
            switch data##pokemon {
            | None => "no pokemon"
            | Some(pokemon) =>
              Js.log(pokemon);
              switch pokemon##name {
              | None => "no pokemon"
              | Some(x) => x
              };
            }
          )
        )
      </div>;
    }
};

let gengarQuery = GengarQuery.make();

let make =
  Graphql.make(
    ~documentNode=[@bs] gql(gengarQuery##query),
    ~component,
    ~make=componentMake,
    ()
  );
