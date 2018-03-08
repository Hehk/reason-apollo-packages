[@bs.module "react-apollo"] external jsClass : ReasonReact.reactClass = "ApolloProvider";

let make = (~client: ReasonApolloClient.ApolloClient.t, children) =>
  ReasonReact.wrapJsForReason(~reactClass=jsClass, ~props={"client": client}, children);


