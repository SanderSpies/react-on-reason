# [ReasonReact](https://reasonml.github.io/reason-react/) - ReasonML / BuckleScript bindings for React.js

[![npm version](https://badge.fury.io/js/reason-react.svg)](https://www.npmjs.com/package/reason-react)
![npm](https://img.shields.io/npm/dt/reason-react)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)
![contributors](https://img.shields.io/github/contributors/reasonml/reason-react)
[![discord](https://img.shields.io/discord/235176658175262720.svg?logo=discord&colorb=blue)](https://discord.gg/reasonml) [![Meercode CI Score](https://meercode.io/badge/reasonml/reason-react?type=ci-score&branch=master)](https://meercode.io/reasonml/reason-react)
[![twitter](https://img.shields.io/twitter/follow/reasonml?style=social)](https://twitter.com/reasonml)

ReasonReact is a safer, simpler way to build React components. You get a great type system with an even better developer experience. Why choose ReasonReact? Read more [here](https://reasonml.github.io/reason-react/docs/en/what-and-why)

ReasonReact is just React.js under the hood. This makes it super easy to integrate with your current Next.js, Create React App, JavaScript, Flowtype or TypeScript project. Learn more about getting started [here](https://reasonml.github.io/reason-react/docs/en/installation#adding-reason-to-an-existing-reactjs-project-create-react-app-nextjs-etc)

> Watch Ricky Vetter's Reason Conf talk, ["Why React is Just Better in Reason"](https://www.youtube.com/watch?v=i9Kr9wuz24g) to learn more about how Facebook & Messenger are using ReasonReact

> Watch Jordan Walke's Reason Conf talk,  ["React to the Future"](https://www.youtube.com/watch?v=5fG_lyNuEAw) to learn more about the future of ReasonML and React

## Example

```reason
/* Greeting.re */

[@react.component]
let make = (~name) => <h1> {React.string("Hello " ++ name)} </h1>
```

See all of our examples [here](https://reasonml.github.io/reason-react/docs/en/simple). For a full application, check out [reason-react-hacker-news](https://github.com/reasonml-community/reason-react-hacker-news).

## Getting Started

[BuckleScript](http://bucklescript.github.io/) is how your ReasonML code gets compiled to Javascript. Every project that uses BuckleScript will have a `bsconfig.json` file (the same way you'd have tsconfig.json in a Typescript project) with project specific settings.

You can install BuckleScript globally or keep it project specific by adding it as a `devDependency`:

```sh
yarn global add bs-platform

# or npm
npm install --global bs-platform
```

If you install BuckleScript globally, you can quickly generate a ReasonReact project template (similar to `create-react-app`):

```sh
bsb -init my-react-app -theme react-hooks
cd my-react-app && npm install && npm start

# in another tab
npm run server
```

If you're interested in adding ReasonReact to your current project, it's a simple 2 step process:

```
yarn add bs-platform --dev --exact

# or npm
npm install bs-platform -D -S
```

Add the appropriate script tags to package.json:

```json
"scripts": {
  "re:build": "bsb -make-world -clean-world",
  "re:watch": "bsb -make-world -clean-world -w"
}
```

Copy the `bsconfig.json` file from our docs located [here](https://reasonml.github.io/reason-react/docs/en/installation#adding-reason-to-an-existing-reactjs-project-create-react-app-nextjs-etc)

Then add some files somewhere (don't forget to change `bsconfig.json`, if needed).

## Using Your Favorite Javascript Libraries

The same way that TypeScript has `type annotations`, we have `bindings`. Bindings are libraries that allow you to import a popular project (like lodash) or to import your own local file. ReasonReact is in fact an example of a binding!

## Documentation

See [https://reasonml.github.io/reason-react](https://reasonml.github.io/reason-react)

## Contribute

We welcome all contributors! Anything from docs to issues to pull requests. Please help us :smile:

```sh
git clone https://github.com/reasonml/reason-react.git
cd reason-react
npm install
npm start
```

See the README inside `src` for more info!

## Editor Support

Looking for syntax highlighting for your favorite editor? Check out [ReasonML Editor Plugins](https://reasonml.github.io/docs/en/editor-plugins)

## Friends of ReasonReact

- [genType](https://github.com/cristianoc/genType) - genType automatically generates bindings for your TypeScript / vanilla JS code.
- [reason-react-native](https://github.com/reason-react-native/reason-react-native) - ReasonML / Bucklescript bindings for React Native. Allows you to use Reason to build an iOS, Android or Web app!
- [reasonml.org](https://reasonml.org/) - An effort by the Reason Association to improve documentation for ReasonML & BuckleScript
- [redex.github.io](https://redex.github.io/) - Find bindings for your favorite libraries here
- [ReasonTown Podcast](https://anchor.fm/reason-town) - ReasonML Podcast
- [ReasonConf Youtube](https://www.youtube.com/channel/UCtFP_Hn5nIbZY4Xi47qfHhw/videos) Reason Conf on Youtube
