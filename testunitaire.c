/*
 gcc     testunitaire.c  Lot_A.c  -o testunitaire -I /usr/local/Cellar/cunit/2.1-3/include/ -lCUnit -L /usr/local/Cellar/cunit/2.1-3/lib/
 */

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "Lot_A.h"

void test_changement_couleur(void){
	plateau P = aleatoire(2,2);
	plateau T = new(2);
	changement_couleur(&T,0,0,P.contenu[0][0]);
	changement_couleur(&T,0,1,P.contenu[0][1]);
	changement_couleur(&T,1,0,P.contenu[1][0]);
	changement_couleur(&T,1,1,P.contenu[1][1]);
	CU_ASSERT_EQUAL(P.contenu[0][0],T.contenu[0][0]);
	CU_ASSERT_EQUAL(P.contenu[1][1],T.contenu[1][1]);
	supprime(&P);
	supprime(&T);
}

void test_colorie_tache(void){
	plateau P = new(2);
	changement_couleur(&P,0,0,0);
	changement_couleur(&P,0,1,0);
	changement_couleur(&P,1,0,0);
	changement_couleur(&P,1,1,1);
	plateau tache = new(2);
	colorie_tache(&P,&tache,2);
	CU_ASSERT_EQUAL(P.contenu[0][0],2);
	CU_ASSERT_EQUAL(P.contenu[0][1],2);
	CU_ASSERT_EQUAL(P.contenu[1][0],2);
	CU_ASSERT_NOT_EQUAL(P.contenu[1][1],2);
	supprime(&P);
	supprime(&tache);
}

void test_victoire(void){
	CU_ASSERT_TRUE(victoire(aleatoire(5,1)));
	plateau P = aleatoire(3,2);
	changement_couleur(&P,0,0,0);
	changement_couleur(&P,0,1,1);
	CU_ASSERT_FALSE(victoire(P));
	supprime(&P);
}

int main() {
	CU_pSuite pSuite = NULL;
	
	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("Suite",NULL,NULL);

	if (pSuite==NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

    if (CU_add_test (pSuite, "test of changement_couleur()",test_changement_couleur)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test (pSuite, "test of colorie_tache()",test_colorie_tache)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test (pSuite, "test of victoire()",test_victoire)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
	
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    //CU_cleanup_registry();
    
	return 0;
}
