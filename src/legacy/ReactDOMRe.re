/* First time reading an OCaml/Reason/BuckleScript file? */
/* `external` is the foreign function call in OCaml. */
/* here we're saying `I guarantee that on the JS side, we have a `render` function in the module "react-dom"
   that takes in a reactElement, a dom element, and returns unit (nothing) */
/* It's like `let`, except you're pointing the implementation to the JS side. The compiler will inline these
   calls and add the appropriate `require("react-dom")` in the file calling this `render` */
[@bs.val] [@bs.module "react-dom"]
external render: (React.element, Dom.element) => unit = "render";

[@bs.val]
external _getElementsByClassName: string => array(Dom.element) =
  "document.getElementsByClassName";

[@bs.val] [@bs.return nullable]
external _getElementById: string => option(Dom.element) =
  "document.getElementById";

let renderToElementWithClassName = (reactElement, className) =>
  switch (_getElementsByClassName(className)) {
  | [||] =>
    Js.Console.error(
      "ReactDOMRe.renderToElementWithClassName: no element of class "
      ++ className
      ++ " found in the HTML.",
    )
  | elements => render(reactElement, Array.unsafe_get(elements, 0))
  };

let renderToElementWithId = (reactElement, id) =>
  switch (_getElementById(id)) {
  | None =>
    Js.Console.error(
      "ReactDOMRe.renderToElementWithId : no element of id "
      ++ id
      ++ " found in the HTML.",
    )
  | Some(element) => render(reactElement, element)
  };

module Experimental = {
  type root = ReactDOM.Experimental.root;

  [@bs.module "react-dom"]
  external unstable_createRoot: Dom.element => root = "unstable_createRoot";

  [@bs.send] external render: (root, React.element) => unit = "render";

  let createRootWithClassName = className =>
    switch (_getElementsByClassName(className)) {
    | [||] => None
    | elements => Some(unstable_createRoot(Array.unsafe_get(elements, 0)))
    };

  let createRootWithId = id =>
    switch (_getElementById(id)) {
    | None => None
    | Some(element) => Some(unstable_createRoot(element))
    };
};

[@bs.val] [@bs.module "react-dom"]
external hydrate: (React.element, Dom.element) => unit = "hydrate";

let hydrateToElementWithClassName = (reactElement, className) =>
  switch (_getElementsByClassName(className)) {
  | [||] =>
    Js.Console.error(
      "ReactDOMRe.hydrateToElementWithClassName: no element of class "
      ++ className
      ++ " found in the HTML.",
    )
  | elements => hydrate(reactElement, Array.unsafe_get(elements, 0))
  };

let hydrateToElementWithId = (reactElement, id) =>
  switch (_getElementById(id)) {
  | None =>
    Js.Console.error(
      "ReactDOMRe.hydrateToElementWithId : no element of id "
      ++ id
      ++ " found in the HTML.",
    )
  | Some(element) => hydrate(reactElement, element)
  };

[@bs.val] [@bs.module "react-dom"]
external createPortal: (React.element, Dom.element) => React.element =
  "createPortal";

[@bs.val] [@bs.module "react-dom"]
external unmountComponentAtNode: Dom.element => unit =
  "unmountComponentAtNode";

[@bs.val] [@bs.module "react-dom"]
external findDOMNode: ReasonReact.reactRef => Dom.element = "findDOMNode";

external domElementToObj: Dom.element => Js.t({..}) = "%identity";

type style = ReactDOM.style;

type domRef = ReactDOM.domRef;

module Ref = {
  type t = domRef;
  type currentDomRef = React.ref(Js.nullable(Dom.element));
  type callbackDomRef = Js.nullable(Dom.element) => unit;

  external domRef: currentDomRef => domRef = "%identity";
  external callbackDomRef: callbackDomRef => domRef = "%identity";
};

include ReactDOM.Props;

[@bs.splice] [@bs.module "react"]
external createDOMElementVariadic:
  (string, ~props: domProps=?, array(React.element)) => React.element =
  "createElement";

external objToDOMProps: Js.t({..}) => props = "%identity";

[@deprecated "Please use ReactDOMRe.props instead"]
type reactDOMProps = props;

[@bs.splice] [@bs.val] [@bs.module "react"]
external createElement:
  (string, ~props: props=?, array(React.element)) => React.element =
  "createElement";

/* Only wanna expose createElementVariadic here. Don't wanna write an interface file */
include (
          /* Use varargs to avoid the ReactJS warning for duplicate keys in children */
          {
            [@bs.val] [@bs.module "react"]
            external createElementInternalHack: 'a = "createElement";
            [@bs.send]
            external apply:
              ('theFunction, 'theContext, 'arguments) =>
              'returnTypeOfTheFunction =
              "apply";

            let createElementVariadic = (domClassName, ~props=?, children) => {
              let variadicArguments =
                [|Obj.magic(domClassName), Obj.magic(props)|]
                |> Js.Array.concat(children);
              createElementInternalHack->(
                                           apply(
                                             Js.Nullable.null,
                                             variadicArguments,
                                           )
                                         );
            };
          }: {
            let createElementVariadic:
              (string, ~props: props=?, array(React.element)) => React.element;
          }
        );

module Style = ReactDOMStyle;
