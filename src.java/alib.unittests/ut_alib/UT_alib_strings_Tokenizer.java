// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alib;
import org.junit.Test;

import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.Tokenizer;

import ut_com_aworx.AWorxUnitTesting;
import ut_com_aworx.UTSampleWriter;


public class UT_alib_strings_Tokenizer extends AWorxUnitTesting
{

//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

static
void documentationSampleTokenizer()
{
    UTSampleWriter utsw= new UTSampleWriter("DOC_SAMPLES_ALIB_LIB_STRING_TOKEN.txt");

//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]
    // data string to tokenize
    AString data= new AString( "test;  abc ; 1,2 , 3 ; xyz ; including;separator" );

    // create tokenizer on data with ';' as delimiter
    Tokenizer tknzr= new Tokenizer( data, ';' );

    // read tokens
    System.out.println( tknzr.next().toString() ); // will print "test"
    System.out.println( tknzr.next().toString() ); // will print "abc"
    System.out.println( tknzr.next().toString() ); // will print "1,2 , 3"

    // tokenize actual (third) token (nested tokenizer)
    Tokenizer subTknzr= new Tokenizer( tknzr.actual,  ',');
    System.out.print( subTknzr.next().toString() );

    while( subTknzr.hasNext() )
        System.out.print( "~" + subTknzr.next().toString() );

    System.out.println();

    // continue with the main tokenizer
    System.out.println( tknzr.next().toString() ); // will print "xyz"

    // grab the rest, as we know that the last token might include our separator character
    System.out.println( tknzr.getRest().toString() ); // will print "including;separator"
//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]

    utsw.flushAndResetSystemOut();
}


@Test
public void DocumentationSamples()
{
    UT_INIT();

    //UT_PRINT("*** Documentation Sample +**")
    documentationSampleTokenizer();
}


static  void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                    Whitespaces trim, int inpStart, int inpEnd  )
{
    Substring inp= new Substring( inputString );
    if ( inpStart >= 0 ) inp.start= inpStart;
    if ( inpEnd   >= 0 ) inp.end=   inpEnd;
    res.clear();

    Tokenizer tknzr= new Tokenizer( inp, delim );

    while( tknzr.hasNext() )
    {
        tknzr.next(trim).copyTo( res, true );
        res._( newDelim );
    }

}

static
void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                    Whitespaces trim, int inpStart  )
{
    tokenizerTest( inputString, res, delim, newDelim, trim, inpStart, -1);
}

static
void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                    Whitespaces trim )
{
    tokenizerTest( inputString, res, delim, newDelim, trim, -1, -1);
}

@SuppressWarnings("static-method")
@Test
public void Tokenize()
{
    UT_INIT();

    AString astr=  new AString();
    AString res=   new AString();

    // tokenizing empty string
    astr.clear()._( "" );
    res.clear();
    {
        Tokenizer tknzr= new Tokenizer( astr, ',' );   UT_EQ( true,  tknzr.hasNext() );
        tknzr.next().copyTo( res, true );              UT_TRUE( res.isEmpty() );
    }

    // tokenizing no delim
    astr.clear()._( "abc" );
    res.clear();
    {
        Tokenizer tknzr= new Tokenizer( astr, ',' );                UT_EQ( true,  tknzr.hasNext() );
        tknzr.next().copyTo( res, true );     UT_EQ( "abc", res );
    }

    // tokenizing
    {
        tokenizerTest( "abc",                res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@",               res );
        tokenizerTest( "a,bc",               res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@bc@",              res );
        tokenizerTest( "a,bc",               res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@bc@",              res );
        tokenizerTest( ",",                  res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@@",                 res );
        tokenizerTest( ",,",                 res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@@@",                res );
        tokenizerTest( "a,b,c,,",            res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@b@c@@@",           res );
        tokenizerTest( "a,b,c",              res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@b@c@",             res );
        tokenizerTest( ",a,b,c",             res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@a@b@c@",            res );
        tokenizerTest( "123567",             res, ',', '@',   Whitespaces.TRIM,  2,    2 );  UT_EQ ( "3@",                 res );
        tokenizerTest( "123567",             res, ',', '@',   Whitespaces.TRIM,  2,    1 );  UT_EQ ( "@",                  res );
        tokenizerTest( "  abc , def , ghe ", res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@def@ghe@",       res );
        tokenizerTest( "abc , def,ghe,",     res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@def@ghe@@",      res );
        tokenizerTest( "  abc , def , ghe ", res, ',', '@',   Whitespaces.KEEP, -1,   -1 );  UT_EQ ( "  abc @ def @ ghe @",res );
        tokenizerTest( "abc , def,ghe,",     res, ',', '@',   Whitespaces.KEEP, -1,   -1 );  UT_EQ ( "abc @ def@ghe@@",    res );
    }

    // tokenizing with different delimiters
    {
        astr.clear()._( "1,5;3@4" );
        Tokenizer tknzr= new Tokenizer(astr, ',');
        tknzr.next()                       .copyTo( res );    UT_EQ ( "1",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, ';' ).copyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, '@' ).copyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, '-' ).copyTo( res );    UT_EQ ( "4",   res );  UT_EQ( false, tknzr.hasNext() );
    }

    // tokenizing with different delimiters
    {
        astr.clear()._( "abc, 5;\t3;;; 4  " );
        Tokenizer tknzr= new Tokenizer(astr,',');
        tknzr.next()                       .copyTo( res );    UT_EQ ( "abc", res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, ';' ).copyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next()                       .copyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next()                       .copyTo( res );    UT_EQ ( "",    res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.getRest()                    .copyTo( res );    UT_EQ ( "; 4", res );  UT_EQ( false, tknzr.hasNext() );
    }

    // sub-tokens
    {
        astr.clear()._( "1,2;3 , 4;5,;," );
        Tokenizer tknzr= new Tokenizer(astr, ';');

        Tokenizer tknzr2= new Tokenizer( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "1", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "2", res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( tknzr.hasNext() );

        tknzr2.set( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "3", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "4", res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( tknzr.hasNext() );

        tknzr2.set( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "5", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "",  res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( tknzr.hasNext() );

        tknzr2.set( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "", res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( !tknzr.hasNext() );
    }

}

}
