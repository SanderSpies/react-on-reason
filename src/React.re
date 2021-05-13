[@text "React bindings for ReasonML"];

[@text "{1 Elements}"];

/** A React element; the equivalent of elements that get created in
    JavaScript with [React.createElement]. */
type element;

/** Use this (instead of e.g. [<span />]) to tell React not to render
    anything. */
[@bs.val] external null: element = "null";

/** [float(value)] casts the float [value] into a React element. */
external float: float => element = "%identity";

/** [int(value)] casts the int [value] into a React element. */
external int: int => element = "%identity";

/** [string(value)] casts the string [value] into a React element. */
external string: string => element = "%identity";

/** [array(value)] casts the element array [value] into a React element. */
external array: array(element) => element = "%identity";

[@text "{1 Components}"];

type componentLike('props, 'return) = 'props => 'return;

/** A React component--a function that takes props and returns a React
    element. */
type component('props) = componentLike('props, element);

/* this function exists to prepare for making `component` abstract */
external component: componentLike('props, element) => component('props) = "%identity";

[@bs.module "react"]
external createElement: (component('props), 'props) => element =
  "createElement";

[@bs.module "react"]
external cloneElement: (element, 'props) => element = "cloneElement";

[@bs.splice] [@bs.module "react"]
external createElementVariadic:
  (component('props), 'props, array(element)) => element =
  "createElement";

[@bs.module "react"] [@deprecated "Please use JSX syntax directly."]
external jsxKeyed: (component('props), 'props, string) => element = "jsx";

[@bs.module "react"] [@deprecated "Please use JSX syntax directly."]
external jsx: (component('props), 'props) => element = "jsx";

[@bs.module "react"] [@deprecated "Please use JSX syntax directly."]
external jsxs: (component('props), 'props) => element = "jsxs";

[@bs.module "react"] [@deprecated "Please use JSX syntax directly."]
external jsxsKeyed: (component('props), 'props, string) => element = "jsxs";

[@text "{1 Refs}"];

type ref('value) = {mutable current: 'value};

module Ref = {
  [@deprecated "Please use the type React.ref instead"]
  type t('value) = ref('value);

  [@deprecated "Please directly read from ref.current instead"] [@bs.get]
  external current: ref('value) => 'value = "current";

  [@deprecated "Please directly assign to ref.current instead"] [@bs.set]
  external setCurrent: (ref('value), 'value) => unit = "current";
};

[@bs.module "react"]
external createRef: unit => ref(Js.nullable('a)) = "createRef";

[@bs.module "react"]
external forwardRef:
  ([@bs.uncurry] (('props, Js.Nullable.t(ref('a))) => element)) =>
  component('props) =
  "forwardRef";

/** Operations for working with React element children. */
module Children = {
  [@bs.module "react"] [@bs.scope "Children"] [@bs.val]
  external map: (element, element => element) => element = "map";
  [@bs.module "react"] [@bs.scope "Children"] [@bs.val]
  external mapWithIndex:
    (element, [@bs.uncurry] ((element, int) => element)) => element =
    "map";
  [@bs.module "react"] [@bs.scope "Children"] [@bs.val]
  external forEach: (element, element => unit) => unit = "forEach";
  [@bs.module "react"] [@bs.scope "Children"] [@bs.val]
  external forEachWithIndex:
    (element, [@bs.uncurry] ((element, int) => unit)) => unit =
    "forEach";
  [@bs.module "react"] [@bs.scope "Children"] [@bs.val]
  external count: element => int = "count";
  [@bs.module "react"] [@bs.scope "Children"] [@bs.val]
  external only: element => element = "only";
  [@bs.module "react"] [@bs.scope "Children"] [@bs.val]
  external toArray: element => array(element) = "toArray";
};

[@text "{1 Context}"];

module Context = {
  type t('props);

  [@bs.obj]
  external makeProps:
    (~value: 'props, ~children: element, unit) =>
    {
      .
      "value": 'props,
      "children": element,
    };

  [@bs.get]
  external provider:
    t('props) =>
    component({
      .
      "value": 'props,
      "children": element,
    }) =
    "Provider";
};

[@bs.module "react"]
external createContext: 'a => Context.t('a) = "createContext";

[@text "{1 Memo}"];

[@bs.module "react"]
external memo: component('props) => component('props) = "memo";

[@bs.module "react"]
external memoCustomCompareProps:
  (component('props), [@bs.uncurry] (('props, 'props) => bool)) =>
  component('props) =
  "memo";

module Fragment = {
  [@bs.obj]
  external makeProps:
    (~children: element, ~key: 'key=?, unit) => {. "children": element};
  [@bs.module "react"]
  external make: component({. "children": element}) = "Fragment";
};

module StrictMode = {
  [@bs.obj]
  external makeProps:
    (~children: element, ~key: 'key=?, unit) => {. "children": element};
  [@bs.module "react"]
  external make: component({. "children": element}) = "StrictMode";
};

module Suspense = {
  [@bs.obj]
  external makeProps:
    (~children: element=?, ~fallback: element=?, ~key: 'key=?, unit) =>
    {
      .
      "children": option(element),
      "fallback": option(element),
    };
  [@bs.module "react"]
  external make:
    component({
      .
      "children": option(element),
      "fallback": option(element),
    }) =
    "Suspense";
};

/** Experimental React.SuspenseList */
module SuspenseList = {
  type revealOrder;
  type tail;
  [@bs.obj]
  external makeProps:
    (
      ~children: element=?,
      ~revealOrder: [@bs.string] [ | `forwards | `backwards | `together]=?,
      ~tail: [@bs.string] [ | `collapsed | `hidden]=?,
      unit
    ) =>
    {
      .
      "children": option(element),
      "revealOrder": option(revealOrder),
      "tail": option(tail),
    };

  [@bs.module "react"]
  external make:
    component({
      .
      "children": option(element),
      "revealOrder": option(revealOrder),
      "tail": option(tail),
    }) =
    "SuspenseList";
};

[@text "{1 Hooks}"];

[@text "{2 State}"];

/*
 * Yeah, we know this api isn't great. tl;dr: useReducer instead.
 * It's because useState can take functions or non-function values and treats
 * them differently. Lazy initializer + callback which returns state is the
 * only way to safely have any type of state and be able to update it correctly.
 */

/** [useState(fn)] is the [useState] hook; it returns a pair of the
    current state, and a state setter function.

    [fn] must be a nullary function that returns the initial state, like
    [() => 0].

    The state setter function (let's call it [setState]) takes a function
    (let's call it [update]) as its argument; [update] gets called by
    React with the current state, and returns the new state. E.g.:

    {[let (count, setCount) = React.useState(() => 0);
setCount(count => count + 1);]}
 */
[@bs.module "react"]
external useState:
  ([@bs.uncurry] (unit => 'state)) => ('state, ('state => 'state) => unit) =
  "useState";

/** [useReducer(reducer, initialState)] is the [useReducer] hook; it
    returns a pair of the current state, and an dispatch function.

    [reducer(currentState, action)] is the new state.

    [initialState] is the state the reducer starts with. */
[@bs.module "react"]
external useReducer:
  ([@bs.uncurry] (('state, 'action) => 'state), 'state) =>
  ('state, 'action => unit) =
  "useReducer";

[@bs.module "react"]
external useReducerWithMapState:
  (
    [@bs.uncurry] (('state, 'action) => 'state),
    'initialState,
    [@bs.uncurry] ('initialState => 'state)
  ) =>
  ('state, 'action => unit) =
  "useReducer";

[@text {|{2 Effect}

The effect hooks take an argument [fn]. [fn()] runs the effect when
called by the React runtime. It also optionally returns a cancellation
function which is called if the component is unmounted.|}];

/** [useEffect(fn)] runs the effect [fn] on every render. */
[@bs.module "react"]
external useEffect: ([@bs.uncurry] (unit => option(unit => unit))) => unit =
  "useEffect";

/** [useEffect0(fn)] runs the effect [fn] on first render only. */
[@bs.module "react"]
external useEffect0:
  ([@bs.uncurry] (unit => option(unit => unit)), [@bs.as {json|[]|json}] _) =>
  unit =
  "useEffect";

/** [useEffect1(fn, deps)] runs the effect [fn] when any of the values in
    the [deps] array changes. [deps] is meant to be used to pass in a
    single value, but can be used to pass in any number of values (as
    long as they are of the same type). */
[@bs.module "react"]
external useEffect1:
  ([@bs.uncurry] (unit => option(unit => unit)), array('a)) => unit =
  "useEffect";

[@text {|The rest of the [useEffect] hooks take different-arity tuples as
their dependencies arguments, to model exact numbers of effect
dependencies.|}];

[@bs.module "react"]
external useEffect2:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b)) => unit =
  "useEffect";
[@bs.module "react"]
external useEffect3:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c)) => unit =
  "useEffect";
[@bs.module "react"]
external useEffect4:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c, 'd)) => unit =
  "useEffect";
[@bs.module "react"]
external useEffect5:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c, 'd, 'e)) =>
  unit =
  "useEffect";
[@bs.module "react"]
external useEffect6:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c, 'd, 'e, 'f)) =>
  unit =
  "useEffect";
[@bs.module "react"]
external useEffect7:
  (
    [@bs.uncurry] (unit => option(unit => unit)),
    ('a, 'b, 'c, 'd, 'e, 'f, 'g)
  ) =>
  unit =
  "useEffect";

[@text {|The following [useLayoutEffect] bindings are modelled similarly
to the [useEffect] bindings.|}];

[@bs.module "react"]
external useLayoutEffect:
  ([@bs.uncurry] (unit => option(unit => unit))) => unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect0:
  ([@bs.uncurry] (unit => option(unit => unit)), [@bs.as {json|[]|json}] _) =>
  unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect1:
  ([@bs.uncurry] (unit => option(unit => unit)), array('a)) => unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect2:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b)) => unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect3:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c)) => unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect4:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c, 'd)) => unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect5:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c, 'd, 'e)) =>
  unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect6:
  ([@bs.uncurry] (unit => option(unit => unit)), ('a, 'b, 'c, 'd, 'e, 'f)) =>
  unit =
  "useLayoutEffect";
[@bs.module "react"]
external useLayoutEffect7:
  (
    [@bs.uncurry] (unit => option(unit => unit)),
    ('a, 'b, 'c, 'd, 'e, 'f, 'g)
  ) =>
  unit =
  "useLayoutEffect";

[@text "{2 Memo}"];

[@bs.module "react"]
external useMemo: ([@bs.uncurry] (unit => 'any)) => 'any = "useMemo";
[@bs.module "react"]
external useMemo0:
  ([@bs.uncurry] (unit => 'any), [@bs.as {json|[]|json}] _) => 'any =
  "useMemo";
[@bs.module "react"]
external useMemo1: ([@bs.uncurry] (unit => 'any), array('a)) => 'any =
  "useMemo";
[@bs.module "react"]
external useMemo2: ([@bs.uncurry] (unit => 'any), ('a, 'b)) => 'any =
  "useMemo";
[@bs.module "react"]
external useMemo3: ([@bs.uncurry] (unit => 'any), ('a, 'b, 'c)) => 'any =
  "useMemo";
[@bs.module "react"]
external useMemo4: ([@bs.uncurry] (unit => 'any), ('a, 'b, 'c, 'd)) => 'any =
  "useMemo";
[@bs.module "react"]
external useMemo5:
  ([@bs.uncurry] (unit => 'any), ('a, 'b, 'c, 'd, 'e)) => 'any =
  "useMemo";
[@bs.module "react"]
external useMemo6:
  ([@bs.uncurry] (unit => 'any), ('a, 'b, 'c, 'd, 'e, 'f)) => 'any =
  "useMemo";
[@bs.module "react"]
external useMemo7:
  ([@bs.uncurry] (unit => 'any), ('a, 'b, 'c, 'd, 'e, 'f, 'g)) => 'any =
  "useMemo";

[@text "{2 Callback}"];

/** This type forces BuckleScript to treat the hook return value as a
    function. */
type callback('input, 'output) = 'input => 'output;

/* TODO: should we even bother to bind the first two? The whole point of
  useCallback is memoizing the callback based on its dependencies; and
  the dependencies need to correct too. */

[@bs.module "react"]
external useCallback:
  ([@bs.uncurry] ('input => 'output)) => callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback0:
  ([@bs.uncurry] ('input => 'output), [@bs.as {json|[]|json}] _) =>
  callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback1:
  ([@bs.uncurry] ('input => 'output), array('a)) => callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback2:
  ([@bs.uncurry] ('input => 'output), ('a, 'b)) => callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback3:
  ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c)) =>
  callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback4:
  ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd)) =>
  callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback5:
  ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd, 'e)) =>
  callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback6:
  ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd, 'e, 'f)) =>
  callback('input, 'output) =
  "useCallback";
[@bs.module "react"]
external useCallback7:
  ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd, 'e, 'f, 'g)) =>
  callback('input, 'output) =
  "useCallback";

[@text "{2 Context}"];

[@bs.module "react"]
external useContext: Context.t('any) => 'any = "useContext";

[@text "{2 Ref}"];

[@bs.module "react"] external useRef: 'value => ref('value) = "useRef";

[@text "{2 Imperative Handle}"];

[@bs.module "react"]
external useImperativeHandle0:
  (
    Js.Nullable.t(ref('value)),
    [@bs.uncurry] (unit => 'value),
    [@bs.as {json|[]|json}] _
  ) =>
  unit =
  "useImperativeHandle";

[@bs.module "react"]
external useImperativeHandle1:
  (Js.Nullable.t(ref('value)), [@bs.uncurry] (unit => 'value), array('a)) =>
  unit =
  "useImperativeHandle";

[@bs.module "react"]
external useImperativeHandle2:
  (Js.Nullable.t(ref('value)), [@bs.uncurry] (unit => 'value), ('a, 'b)) =>
  unit =
  "useImperativeHandle";

[@bs.module "react"]
external useImperativeHandle3:
  (
    Js.Nullable.t(ref('value)),
    [@bs.uncurry] (unit => 'value),
    ('a, 'b, 'c)
  ) =>
  unit =
  "useImperativeHandle";

[@bs.module "react"]
external useImperativeHandle4:
  (
    Js.Nullable.t(ref('value)),
    [@bs.uncurry] (unit => 'value),
    ('a, 'b, 'c, 'd)
  ) =>
  unit =
  "useImperativeHandle";

[@bs.module "react"]
external useImperativeHandle5:
  (
    Js.Nullable.t(ref('value)),
    [@bs.uncurry] (unit => 'value),
    ('a, 'b, 'c, 'd, 'e)
  ) =>
  unit =
  "useImperativeHandle";

[@bs.module "react"]
external useImperativeHandle6:
  (
    Js.Nullable.t(ref('value)),
    [@bs.uncurry] (unit => 'value),
    ('a, 'b, 'c, 'd, 'e, 'f)
  ) =>
  unit =
  "useImperativeHandle";

[@bs.module "react"]
external useImperativeHandle7:
  (
    Js.Nullable.t(ref('value)),
    [@bs.uncurry] (unit => 'value),
    ('a, 'b, 'c, 'd, 'e, 'f, 'g)
  ) =>
  unit =
  "useImperativeHandle";

/** Uncurried versions of the hooks bindings. Use these if you want to
    handle currying/not currying explicitly instead of letting
    BuckleScript do it. */
module Uncurried = {
  [@bs.module "react"]
  external useState:
    ([@bs.uncurry] (unit => 'state)) =>
    ('state, (. ('state => 'state)) => unit) =
    "useState";

  [@bs.module "react"]
  external useReducer:
    ([@bs.uncurry] (('state, 'action) => 'state), 'state) =>
    ('state, (. 'action) => unit) =
    "useReducer";

  [@bs.module "react"]
  external useReducerWithMapState:
    (
      [@bs.uncurry] (('state, 'action) => 'state),
      'initialState,
      [@bs.uncurry] ('initialState => 'state)
    ) =>
    ('state, (. 'action) => unit) =
    "useReducer";

  type callback('input, 'output) = (. 'input) => 'output;

  [@bs.module "react"]
  external useCallback:
    ([@bs.uncurry] ('input => 'output)) => callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback0:
    ([@bs.uncurry] ('input => 'output), [@bs.as {json|[]|json}] _) =>
    callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback1:
    ([@bs.uncurry] ('input => 'output), array('a)) =>
    callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback2:
    ([@bs.uncurry] ('input => 'output), ('a, 'b)) =>
    callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback3:
    ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c)) =>
    callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback4:
    ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd)) =>
    callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback5:
    ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd, 'e)) =>
    callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback6:
    ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd, 'e, 'f)) =>
    callback('input, 'output) =
    "useCallback";
  [@bs.module "react"]
  external useCallback7:
    ([@bs.uncurry] ('input => 'output), ('a, 'b, 'c, 'd, 'e, 'f, 'g)) =>
    callback('input, 'output) =
    "useCallback";
};

[@text "{2 Transition}"];

type transitionConfig = {timeoutMs: int};

[@bs.module "react"]
external useTransition:
  (~config: transitionConfig=?, unit) =>
  (callback(callback(unit, unit), unit), bool) =
  "useTransition";

[@text "{1 Display Name}"];

/** [setDisplayName(component, name)] sets the React [component]'s
    display name. */
[@bs.set]
external setDisplayName: (component('props), string) => unit = "displayName";

/** [displayName(component)] is the [component]'s display name or [None]. */
[@bs.get] [@bs.return nullable]
external displayName: component('props) => option(string) = "displayName";
