open Data;
let update action state => {
  switch action {
  | NoOp => (state, Eff.none)
  | UpdateLoginForm loginForm => ({...state, loginForm}, Eff.none)
  | Login loginForm  => ({...state, session: Pending}, Eff.login loginForm)
  | LoginSuccess session => 
    (
      {
        ...state, 
        loginForm: emptyLoginForm, 
        session: Ready session,
        page: Home
      }, 
      Eff.none
    )
  | LoginError err => ({...state, session: Error err}, Eff.none)
  | SelectVisitorType visitorType => {
    let visitorForm = {...state.visitorForm, visitorType};
    ({...state, visitorForm}, Eff.none)
  }
  | SelectVisitorInterests visitorInterests => {
    let visitorForm = {...state.visitorForm, visitorInterests};
    ({...state, visitorForm}, Eff.none)
  }
  | UpdateVisitorForm visitorForm => ({...state, visitorForm}, Eff.none)
  | SubmitVisitorForm _ => (state, Eff.none)
  | SubmitVisitorFormError _ => (state, Eff.none)
  | SubmitVisitorFormSuccess => (state, Eff.none)
  };
};

let render state dispatch => {
  let {session, loginForm, visitorForm} = state;
  switch state.page {
  | Login => <LoginPage session dispatch loginForm />
  | Home => <HomePage  dispatch />
  | VisitorInterests => <VisitorInterestsPage  dispatch />
  | VisitorDetails => <VisitorDetailsPage visitorForm dispatch />
  | ThankYou => <ThankYouPage dispatch />
  };
};

let app () => <App init=Data.emptyModel update render />;
