let cache = ApolloCacheInmemory.make();

let link = ApolloLinkHttp.make(~uri="http://localhost:5000/", ());

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

[@bs.module]
external gql : [@bs] (string => ApolloClient.queryString) = "graphql-tag";

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
