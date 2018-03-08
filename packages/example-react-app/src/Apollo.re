open ReasonApolloCacheInmemory;

open ReasonApolloClient;

let cache = ApolloCacheInmemory.make();

let link =
  ApolloLinkHttp.make(~uri="http://localhost:5000/", ());

let client = ApolloClient.make(~link, ~cache, ());
