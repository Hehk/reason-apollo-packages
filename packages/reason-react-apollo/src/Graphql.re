open ReasonApolloClient;

[@bs.module "react-apollo"]
external graphql :
  ReasonApolloClient.ApolloClient.documentNode =>
  [@bs] (ReasonReact.reactClass => ReasonReact.reactClass) =
  "";

type apolloResponse('a) = {
  loading: bool,
  variables: Js.Json.t,
  error: option(ApolloClient.graphqlError),
  result: option('a)
};

external castResponse : Js.t({..}) => Js.Json.t = "%identity";

let make = (~documentNode, ~parse, ~component, ~make, ()) => {
  let graphqlWrapper = graphql(documentNode);
  let jsComponent =
    ReasonReact.wrapReasonForJs(
      ~component,
      props => {
        let loading = Js.to_bool(props##data##loading);
        let result =
          if (loading) {
            None;
          } else {
            Some(parse(castResponse(props##data)));
          };
        let data = {
          variables: props##variables,
          error: Js.Nullable.toOption(props##error),
          loading,
          result
        };
        make(~data, [||]);
      }
    );
  let reactClass = [@bs] graphqlWrapper(jsComponent);
  (children: array(ReasonReact.reactElement)) =>
    ReasonReact.wrapJsForReason(~reactClass, ~props=Js.Obj.empty(), children);
};
