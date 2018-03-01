let cache = ApolloCacheInmemory.make();
let link = ApolloLinkHttp.make();

Js.log(cache);

let client = ApolloClient.make(~link, ~cache, ());

Js.log(client);
