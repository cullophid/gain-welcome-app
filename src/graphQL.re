
let url = Config.host ^ "/graphql";
let (<<) f g a => f (g a);
let (>>) f g a => g (f a);
let jslog key a => {
  Js.log2 key a;
  a
};
let decodeError json => {
  open Json.Decode;
  let decoder = at ["message"] string |> list |> at ["errors"];
  Util.decode decoder json
    |> Result.chain (fun x => x |> Lst.head |> Result.fromOption "Missing Error")
};
let validateResponse json => {
  switch (decodeError json) {
  | Result.Error _ => Task.succeed json 
  | Result.Ok err => Task.fail err
  }
};

let fetch body => {
  open Bs_fetch;

  let makeRequest body jwt => {
    let token = Option.withDefault "" jwt; 
    RequestInit.make
      method_::Post
      headers::(HeadersInit.make {"content-type": "application/json", "Authorization": token})
      body:: (BodyInit.make body)
      ();
  };

  let execute req => { 
    Task.fromLazyPromise 
      (fun () => fetchWithInit url req |> Js.Promise.then_ Response.json)
      |> Task.biMap (fun err => err##message) (fun x => x)
  };

  AsyncStorage.getItem "jwt"
    |> Task.map (makeRequest body)
    |> Task.chain execute
};

let request query variables => {
  Js.Json.stringifyAny { "query": query, "variables": variables }
    |> Task.fromOption "Could not parse query"
    |> Task.chain fetch
    |> Task.chain validateResponse
    |> Task.biMap  (jslog "RequestError") (jslog "RequestSuccess")
};




