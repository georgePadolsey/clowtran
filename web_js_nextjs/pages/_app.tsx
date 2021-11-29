import * as React from "react";
import CssBaseline from "@mui/material/CssBaseline";
import { AppProps } from "next/dist/shared/lib/router/router";
import Head from "next/head";

const LowtranApp = ({ Component, pageProps }: AppProps) => {
  return (
    <>
      <Head>
        <meta name="viewport" content="initial-scale=1, width=device-width" />
      </Head>
      <CssBaseline />
      <Component {...pageProps} />
      {/* The rest of your application */}
    </>
  );
};

export default LowtranApp;
