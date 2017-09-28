/**
 * Copyright (c) 2017-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

const siteConfig = {
  title: "Reason React" /* title for your website */,
  tagline: "A safer, simpler way to build React components in Reason.",
  url: "https://reasonml.github.io/reason-react" /* your github url */,
  editUrl: "https://github.com/reasonml/reason-react/tree/master/docs/",
  recruitingLink: "https://crowdin.com/project/reason-react",
  sourceCodeButton: null,
  baseUrl: "/reason-react/" /* base url for your project */,
  projectName: "reason-react",
  headerLinks: [
    { doc: "getting-started", label: "Docs" },
    { doc: "simple", label: "Examples" },
    { blog: true, label: "Blog" },
    { doc: "community", label: "Community" },
    { href: "https://github.com/reasonml/reason-react", label: "GitHub" },
  ],
  users: [],
  /* path to images for header/footer */
  headerIcon: "img/reason-react-white.svg",
  footerIcon: "img/reason-react-white.svg",
  favicon: "img/favicon/favicon.png",
  /* colors for website */
  colors: {
    primaryColor: "#db4d3f",
    secondaryColor: "#db4d3f",
    prismColor:
      "rgba(219, 77, 63, 0.03)" /* primaryColor in rgba form, with 0.03 alpha */
  }
};

module.exports = siteConfig;
