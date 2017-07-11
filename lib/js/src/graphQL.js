// Generated by BUCKLESCRIPT VERSION 1.8.1, PLEASE EDIT WITH CARE
'use strict';

var Lst          = require("./lst.js");
var Task         = require("./task.js");
var Util         = require("./util.js");
var Curry        = require("bs-platform/lib/js/curry.js");
var Config       = require("./config.js");
var Option       = require("./option.js");
var Result       = require("./result.js");
var Bs_fetch     = require("bs-fetch/lib/js/src/bs_fetch.js");
var Json_decode  = require("bs-json/lib/js/src/json_decode.js");
var AsyncStorage = require("./asyncStorage.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");

var url = Config.host + "/graphql";

function $less$less(f, g, a) {
  return Curry._1(f, Curry._1(g, a));
}

function $great$great(f, g, a) {
  return Curry._1(g, Curry._1(f, a));
}

function jslog(key, a) {
  console.log(key, a);
  return a;
}

function decodeError(json) {
  var partial_arg = Json_decode.at(/* :: */[
        "message",
        /* [] */0
      ], Json_decode.string);
  var decoder = Json_decode.at(/* :: */[
        "errors",
        /* [] */0
      ], (function (param) {
          return Json_decode.list(partial_arg, param);
        }));
  return Result.chain((function (x) {
                return Result.fromOption("Missing Error", Lst.head(x));
              }), Util.decode(decoder, json));
}

function validateResponse(json) {
  var match = decodeError(json);
  if (match.tag) {
    return Task.fail(match[0]);
  } else {
    return Task.succeed(json);
  }
}

function fetch$1(body) {
  var execute = function (req) {
    return Task.biMap((function (err) {
                  return err.message;
                }), (function (x) {
                  return x;
                }), Task.fromLazyPromise((function () {
                      return fetch(url, req).then((function (prim) {
                                    return prim.json();
                                  }));
                    })));
  };
  return Task.chain(execute, Task.map((function (param) {
                    var body$1 = body;
                    var jwt = param;
                    var token = Option.withDefault("", jwt);
                    return Curry.app(Bs_fetch.RequestInit[/* make */0], [
                                /* Some */[/* Post */2],
                                /* Some */[{
                                    "content-type": "application/json",
                                    Authorization: token
                                  }],
                                /* Some */[body$1],
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* () */0
                              ]);
                  }), AsyncStorage.getItem("jwt")));
}

function request(query, variables) {
  return Task.biMap((function (param) {
                return jslog("RequestError", param);
              }), (function (param) {
                return jslog("RequestSuccess", param);
              }), Task.chain(validateResponse, Task.chain(fetch$1, Task.fromOption("Could not parse query", Js_primitive.undefined_to_opt(JSON.stringify({
                                  query: query,
                                  variables: variables
                                }))))));
}

exports.url              = url;
exports.$less$less       = $less$less;
exports.$great$great     = $great$great;
exports.jslog            = jslog;
exports.decodeError      = decodeError;
exports.validateResponse = validateResponse;
exports.fetch            = fetch$1;
exports.request          = request;
/* Config Not a pure module */