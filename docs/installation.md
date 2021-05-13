---
title: Installation
---

**Note**: for general Reason + BuckleScript editor setup, see [here](https://reasonml.github.io/docs/en/editor-plugins).

## BuckleScript

[BuckleScript](http://bucklescript.github.io/) is the tool that compiles ReasonML code to JavaScript. Every project that uses BuckleScript will have a `bsconfig.json` file (the same way you'd have `tsconfig.json` in a Typescript project) with project specific settings. You can install it globally or keep it project specific by adding it as a `devDependency`.

### Using Bucklescript init

BuckleScript's [bsb](https://bucklescript.github.io/docs/en/build-overview.html) build system has an `init` command that generates a project template. The `react-hooks` theme happens to be our official, lightweight template optimized for low learning overhead and ease of integration into an existing project.

The `.re` files compile to straightforward `.bs.js` files. You can open `index.html` directly from the file system. No server needed! Change any `.re` file to see that page automatically refreshed.

```sh
# you can use yarn too (yarn global add bs-platform)
npm install --global bs-platform

# creates project folder
bsb -init my-react-app -theme react-hooks

# cd into that folder, npm install, start
cd my-react-app && npm install && npm start

# in another tab
npm run server
```

### Adding Reason to an existing React.js Project (Create React App, Next.js, etc.)

Set up is very straight forward! Install two dependencies, add some scripts and create a bsconfig.json file.

Install the following dependencies:

```sh
yarn add bs-platform --dev --exact
yarn add reason-react --exact
```

Add scripts to `package.json`:

```json
"scripts": {
  "re:build": "bsb -make-world -clean-world",
  "re:watch": "bsb -make-world -clean-world -w"
}
```

Create a `bsconfig.json` file in the root of your project with the following. All the settings are already defaults, most of this is boilerplate. The important fields are `name`, `bs-dependencies` and `ppx-flags`. As you can see, we've added `reason-react`. This tells Reason where to look for bindings (similar to dependencies in your package.json).

```json
{
  "name": "your-project-name",
  "reason": { "react-jsx": 3 },
  "bsc-flags": ["-bs-super-errors"],
  "sources": [
    {
      "dir": "src",
      "subdirs": true
    }
  ],
  "package-specs": [
    {
      "module": "es6",
      "in-source": true
    }
  ],
  "suffix": ".bs.js",
  "namespace": true,
  "bs-dependencies": [
    "reason-react"
  ],
  "ppx-flags": [],
  "refmt": 3
}
```

That's it!

**Note**: You'll have to run the reason compiler in a separate terminal. First start your project `yarn start` and in a separate terminal run: `yarn re:watch`
