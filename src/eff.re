open Data;
open Action;

type t 'a = option (Task.t 'a 'a);

let (>>) f g x => x |> f |> g;
let none = None;

let delay ms action => Some (Util.delay ms |> Task.map (fun () => action));

let login ({email, password}:LoginForm.t) => {
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

  let decodeSession = Util.decode (Json.Decode.at ["data", "authenticate"] Session.decoder);
  let task = GraphQL.request query variables
    |> Task.map decodeSession
    |> Task.chain Task.fromResult
    |> Task.chain (fun (sess:Session.t) => {
        AsyncStorage.setItem "jwt" sess.token
          |> Task.map (fun _ => sess);
    })
    |> Task.biMap (fun err => LoginError err) (fun ok => LoginSuccess ok);
  Some task;
};

let enqueue visitorForm => {
  let query = "
    query Enqueue($visitorForm: VisitorInput, $queue: String) {
      session {
        dealership {
          queue(id: $queue) {
            enqueue(visitor: $visitorForm) {
              id, 
              name,
              mobile,
              type,
              position
            }
          }
        }
      }
    }
  ";
  let variables = {
    "visitorForm": visitorForm |> VisitorForm.encoder,
    "queue": visitorForm.queue
  };
  let decodeVisitor json => Util.decode (Json.Decode.at ["data", "session", "dealership", "queue", "enqueue"] Visitor.decoder) json
    |> Task.fromResult;


  let task = GraphQL.request query variables
    |> Task.map (fun res => {Js.log2 "RES" res; res;})
    |> Task.chain decodeVisitor
    |> Task.biMap (fun err => SubmitVisitorFormError err) (fun v => SubmitVisitorFormSuccess v);
  
    Some task;
};

let fetchQueues () => {
  let query = "
    query FetchQueues {
      session {
        dealership {
          queues {
            id, 
            name, 
            description,
            order
          }
        }
      }
    }
  ";
  let decodeQueues json => json 
    |> Util.decode (Json.Decode.at ["data", "session", "dealership", "queues"] (Json.Decode.list Queue.decoder))
    |> Task.fromResult;


  let task = GraphQL.request query {js||js}
    |> Task.chain decodeQueues
    |> Task.biMap (fun err => FetchQueuesError err) (fun qs => FetchQueuesSuccess qs);
  Some task;
};