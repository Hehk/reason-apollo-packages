[@bs.module "react-apollo"]
external graphql :
  ReasonApolloClient.ApolloClient.documentNode =>
  [@bs] (ReasonReact.reactClass => ReasonReact.reactClass) =
  "";

let make = (~documentNode, ~component, ~make, ()) => {
  let graphqlWrapper = graphql(documentNode);
  let jsComponent =
    ReasonReact.wrapReasonForJs(~component, jsProps =>
      make(~data=jsProps##data, [||])
    );
  let reactClass = [@bs] graphqlWrapper(jsComponent);
  (children: array(ReasonReact.reactElement)) =>
    ReasonReact.wrapJsForReason(~reactClass, ~props=Js.Obj.empty(), children);
};
