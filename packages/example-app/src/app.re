let cache = ApolloCacheInmemory.make();

let httpLink = ApolloLinkHttp.make(~uri="http://localhost:5000/", ());

let customLink =
  ApolloLink.make((operation, forward) =>
    ApolloLink.Operation.(
      switch forward {
      | None => None
      | Some(x) =>
        setContext(context => context |> Js.Obj.assign({"hello": "world"}), operation);
        Some(x(operation));
      }
    )
  );

let customLink2 =
  ApolloLink.make((operation, forward) =>
    switch forward {
    | None => None
    | Some(x) =>
      Js.log(ApolloLink.Operation.getContext(operation));
      Some(x(operation));
    }
  );

let link = ApolloLink.fromList([customLink, customLink2, httpLink]);

let client = ApolloClient.make(~link, ~cache, ());

let query = {|
{
  pokemon(name:"Gengar") {
    name
    attacks {
      fast {
        name
      }
    }
  }
}
|};

[@bs.module] external gql : [@bs] (string => ApolloClient.queryString) = "graphql-tag";

ApolloClient.query(
  {"query": [@bs] gql(query), "variables": Js.Json.object_(Js.Dict.empty())},
  client
)
|> Js.Promise.then_(value => {
     Js.log2("resolved", value##data);
     Js.Promise.resolve();
   })
|> Js.Promise.catch(err => {
     Js.log2("error", err);
     Js.Promise.resolve();
   });
