import './App.css';
import { BrowserRouter, Switch, Route } from "react-router-dom";
import CurrentMessage from "./presenters/currentMessage";
import NewMessage from "./presenters/newMessage";
import Header from './presenters/header';
import SignUp from './presenters/signUp';
import SignIn from './presenters/signIn';
import HomeMenu from './presenters/homeMenu';
import HomeMessage from './presenters/homeMessage';
import About from './presenters/about';

function App() {
  return (
    <BrowserRouter>
      <div className="App">
        <Header />
        <Switch>
          <Route exact path = "/">
            <div className="HomePage">
              <div className="parentHomePage">
                <div className="childHomePage">
                    <SignIn />
                </div>
                <div className="childHomePage">
                  <HomeMenu />
                </div>
              </div> 
            </div>
          </Route>

          <Route exact path = "/signup">
            <div className="HomePage">
              <div className="parentHomePage">
                <div className="childHomePage">
                    <SignUp />
                </div>
                <div className="childHomePage">
                  <HomeMenu />
                </div>
              </div> 
            </div>
          </Route>

          <Route exact path = "/messages">
            <div className="HomePage">
              <div className="parentHomePage">
                <div className="childHomePage">
                    <HomeMessage />
                </div>
                <div className="childHomePage">
                  <HomeMenu />
                </div>
              </div> 
            </div>
          </Route>

          <Route exact path = "/about">
            <div className="HomePage">
              <div className="parentHomePage">
                <div className="childHomePage">
                    <About />
                </div>
                <div className="childHomePage">
                  <HomeMenu />
                </div>
              </div> 
            </div>
          </Route>

          <Route path="/currentmessage" component={CurrentMessage} />
          <Route path="/newmessage" component={NewMessage} />
        </Switch>
      </div>
    </BrowserRouter>
  );
}

export default App;
