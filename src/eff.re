open Data;
type t 'a = option (Task.t 'a 'a);
let none = None;
let login ({email, password}:loginForm) => {
  let query = "
    query Authenticate($email: String!, $password:String!) {
      authenticate(email: $email, password:$password) {
        token,
        user {
          id,
          email,
          forenames,
          lastname
          dealership {
            id,
            name
          }
        }
      }
    }
  ";
  let variables = {
    "email": email,
    "password": password
  };

  let decodeSession = Util.decode (Json.Decode.at ["data", "authenticate"] Data.sessionDecoder);
  let task = GraphQL.request query variables
    |> Task.map (fun x => {Js.log2 "RES" x; x})
    |> Task.map decodeSession
    |> Task.chain Task.fromResult
    |> Task.chain (fun sess => {
        AsyncStorage.setItem "jwt" sess.token
          |> Task.map (fun _ => sess);
    })
    |> Task.biMap (fun err => LoginError err) (fun ok => LoginSuccess ok);
  Some task;
};


