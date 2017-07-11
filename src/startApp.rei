type dispatch 'action = 'action => unit;
let make : 
  init::'state => 
  update::('action => 'state => ('state, option (Task.t 'action 'action))) => 
  render::('state => dispatch 'action => unit) => 
  dispatch 'action;