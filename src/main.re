open Data;
open Action;
open Model;
let update action state => {
  switch action {
  | NoOp => (state, Eff.none)
  | Goto page => ({...state, page}, Eff.none)
  | UpdateLoginForm loginForm => ({...state, loginForm}, Eff.none)
  | Login loginForm  => ({...state, session: Pending}, Eff.login loginForm)
  | LoginSuccess session => 
    (
      {
        ...state, 
        loginForm: LoginForm.empty, 
        session: Ready session,
        page: Home
      }, 
      Eff.fetchQueues ()
    )
  | LoginError err => ({...state, session: Error err}, Eff.none)
  | SetVisitorType type' => {
    let visitorForm = {...state.visitorForm, type'};
    ({...state, visitorForm, page: VisitorInterests}, Eff.none)
  }
  | SetVisitorQueue queue => {
    let visitorForm = {...state.visitorForm, queue: Ready queue};
    ({...state, visitorForm, page: VisitorDetails}, Eff.none)
  }
  | UpdateVisitorForm visitorForm => ({...state, visitorForm}, Eff.none)
  | SubmitVisitorForm visitorForm => ({...state, visitor: Pending}, Eff.enqueue visitorForm)
  | SubmitVisitorFormError err => ({...state, visitor: Error err}, Eff.none)
  | SubmitVisitorFormSuccess visitor => ({...state, visitor: Ready visitor, page: ThankYou}, Eff.delay 5000 Reset)
  | Reset => ({...state, visitor: NotAsked, visitorForm: VisitorForm.empty, page: Home}, Eff.none)
  | FetchQueuesError err => ({...state, queues: Error err}, Eff.none)
  | FetchQueuesSuccess queues => ({...state, queues: Ready queues}, Eff.none)
  };
};

let render state _dispatch => {
  let dispatch a => {
    Js.log2 "ACTION" @@ Data.Action.toString a;
    _dispatch a
  };
  let {session, loginForm, visitorForm, visitor, queues} = state;
  switch state.page {
  | Login => <LoginPage session dispatch loginForm />
  | Home => <HomePage  dispatch />
  | VisitorInterests => <VisitorInterestsPage dispatch queues />
  | VisitorDetails => <VisitorDetailsPage visitorForm dispatch visitor />
  | ThankYou => <ThankYouPage dispatch visitor />
  };
};

let app () => <App init=Model.empty update render />;
